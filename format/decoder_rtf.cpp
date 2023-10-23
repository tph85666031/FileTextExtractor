#include "com_log.h"
#include "com_file.h"
#include "comex_iconv.h"
#include "decoder_rtf.h"

FileDecoderRtf::FileDecoderRtf()
{
}

FileDecoderRtf::~FileDecoderRtf()
{
}


FormatResult FileDecoderRtf::decode(const char* file_path)
{
    CPPBytes data = com_file_readall(file_path);
    return decode(data);
}

FormatResult FileDecoderRtf::decode(const CPPBytes& content)
{
    FormatResult result;
    std::string text;
    const char* p = (const char*)content.getData();
    parseGroup(p, text);
    result.text.append(text.c_str());
    return result;
}

const char* FileDecoderRtf::parseGroup(const char* content, std::string& text)
{
    //std::vector<uint8> non_ascii;
    std::string non_ascii;
    do
    {
        if(isGroupBegin(content))
        {
            content = parseGroup(content + 1, text);
        }
        else if(isGroupEnd(content))
        {
            content++;
            break;
        }
        else if(isControlWordBegin(content))
        {
            std::string control_word;
            content = detachControlWord(content, control_word);
            control_words.push_back(control_word);
        }
        else if(isControlSymbolBegin(content))
        {
            std::string control_symbol;
            content = detachControlSymbol(content, control_symbol);
            if(control_symbol == "\\'")
            {
                char tmp[3];
                tmp[0] = content[0];
                tmp[1] = content[1];
                tmp[2] = '\0';
                non_ascii.push_back(strtoul(tmp, NULL, 16));
                content += 2;
            }
        }
        else
        {
            if(non_ascii.empty() == false)
            {
                CPPBytes utf8 = comex_iconv_convert("UTF-8//IGNORE", getCodePage().c_str(), non_ascii.data(), non_ascii.length());
                text.append(utf8.toString());
                non_ascii.clear();
            }
            text.push_back(*content);
            content++;
        }
    }
    while(content != NULL && *content != '\0');

    if(non_ascii.empty() == false)
    {
        CPPBytes utf8 = comex_iconv_convert("UTF-8//IGNORE", getCodePage().c_str(), non_ascii.data(), non_ascii.length());
        text.append(utf8.toString());
        non_ascii.clear();
    }
    return content;
}

const char* FileDecoderRtf::detachControlWord(const char* content, std::string& control_word)
{
    if(content == NULL || content[0] != '\\')
    {
        return content;
    }
    control_word.push_back(*content);
    const char* p = content + 1;
    do
    {
        if(*p == ' ' || (isAlpha(*p) == false && isNumber(*p) == false))
        {
            break;
        }
        control_word.push_back(*p);
        p++;
    }
    while(*p);
    return p;
}

const char* FileDecoderRtf::detachControlSymbol(const char* content, std::string& control_symbol)
{
    if(content == NULL || content[0] != '\\')
    {
        return content;
    }
    control_symbol.push_back(content[0]);
    control_symbol.push_back(content[1]);
    return (content + 2);
}

bool FileDecoderRtf::isGroupBegin(const char* content)
{
    if(content == NULL || content[0] == '\0')
    {
        return false;
    }
    return (content[0] == '{');
}

bool FileDecoderRtf::isGroupEnd(const char* content)
{
    if(content == NULL || content[0] == '\0')
    {
        return false;
    }
    return (content[0] == '}');
}

bool FileDecoderRtf::isControlWordBegin(const char* content)
{
    if(content == NULL || content[0] == '\0' || content[1] == '\0')
    {
        return false;
    }
    return (content[0] == '\\' && isAlphaLower(content[1]));
}


bool FileDecoderRtf::isControlSymbolBegin(const char* content)
{
    if(content == NULL || content[0] == '\0' || content[1] == '\0')
    {
        return false;
    }
    return (content[0] == '\\' && isAlpha(content[1]) == false && isNumber(content[1]) == false);
}


bool FileDecoderRtf::isAlpha(char c)
{
    return (isAlphaLower(c) || isAlphaUpper(c));
}

bool FileDecoderRtf::isAlphaLower(char c)
{
    return (c >= 'a' && c <= 'z');
}

bool FileDecoderRtf::isAlphaUpper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

bool FileDecoderRtf::isNumber(char n)
{
    return (n >= '0' && n <= '9');
}

std::string FileDecoderRtf::getCodePage()
{
    if(control_words.size() < 3)
    {
        return std::string();
    }
    if(control_words[1] == "\\ansi")
    {
        if(com_string_start_with(control_words[2].c_str(), "\\ansicpg"))
        {
            int cp = strtol(control_words[2].c_str() + 8, NULL, 10);
            return com_string_format("CP%d", cp);
        }
        return "ASCII";
    }

    return std::string();
}

