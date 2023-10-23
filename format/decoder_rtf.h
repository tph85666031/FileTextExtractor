#ifndef __DECODER_RTF_H__
#define __DECODER_RTF_H__

#include "format.h"

class FileDecoderRtf
{
public:
    FileDecoderRtf();
    virtual ~FileDecoderRtf();

    FormatResult decode(const char* file_path);
    FormatResult decode(const CPPBytes& content);

private:
    const char* parseGroup(const char* content, std::string& text);
    const char* detachControlWord(const char* content, std::string& control_word);
    const char* detachControlSymbol(const char* content, std::string& control_symbol);
    bool isGroupBegin(const char* content);
    bool isGroupEnd(const char* content);
    bool isControlWordBegin(const char* content);
    bool isControlSymbolBegin(const char* content);
    bool isAlpha(char c);
    bool isAlphaLower(char c);
    bool isAlphaUpper(char c);
    bool isNumber(char n);
    std::string getCodePage();
private:
    std::vector<std::string> control_words;
};


#endif /* __DECODER_RTF_H__ */

