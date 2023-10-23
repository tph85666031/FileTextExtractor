#include "com_log.h"
#include "com_file.h"
#include "comex_iconv.h"
#include "decoder_ppt.h"
#include "compoundfilereader.h"
#include "utf.h"

#define RECORD_TYPE_TEXT_CHARS   0x0FA0
#define RECORD_TYPE_TEXT_BYTES   0x0FA8
#define RECORD_TYPE_SLIDE_LIST   0x0FF0
#define RECORD_TYPE_CSTRING      0x0FBA

FileDecoderPpt::FileDecoderPpt()
{
}

FileDecoderPpt::~FileDecoderPpt()
{
}

FormatResult FileDecoderPpt::decode(const char* file_path)
{
    return decode(com_file_readall(file_path));
}

FormatResult FileDecoderPpt::decode(const CPPBytes& content)
{
    FormatResult result;
    CFB::CompoundFileReader reader(content.getData(), content.getDataSize());

    reader.EnumFiles(reader.GetRootEntry(), -1,
                     [&](const CFB::COMPOUND_FILE_ENTRY * entry, const CFB::utf16string & dir, int level)->void
    {
        std::string name = UTF16ToUTF8(entry->name);
        if(reader.IsStream(entry) && entry->size > sizeof(PPT_RECORD))
        {
            LOG_D("name=%s,size=%lu", name.c_str(), entry->size);
            char* buf = new char[entry->size];
            reader.ReadFile(entry, 0, buf, entry->size);
            decodeTextArray(result.text, (const uint8*)buf, entry->size);
            delete[] buf;
        }
    });

    return result;
}

void FileDecoderPpt::decodeText(CPPBytes& text, const uint8* data, int data_size)
{
    if(data == NULL || data_size < (int)sizeof(PPT_RECORD))
    {
        return;
    }
    PPT_RECORD* header = (PPT_RECORD*)data;
    if(header->ver == 0x0F)
    {
        decodeTextArray(text, header->data, header->len);
    }
    else if(header->type == RECORD_TYPE_TEXT_BYTES)
    {
        std::string str_ansi((char*)header->data, header->len);
        std::string utf8 = com_string_ansi_to_utf8(str_ansi);
        text.append(utf8.c_str());
        text.append("\n");
    }
    else if(header->type == RECORD_TYPE_TEXT_CHARS
            || header->type == RECORD_TYPE_CSTRING)
    {
        CPPBytes text_u16(header->data, header->len);
        text.append(comex_iconv_utf16_to_utf8(text_u16));
        text.append("\n");
    }
    else if(header->type == RECORD_TYPE_SLIDE_LIST)
    {
        decodeTextArray(text, header->data, header->len);
    }
}

void FileDecoderPpt::decodeTextArray(CPPBytes& text, const uint8* data, int data_size)
{
    if(data == NULL || data_size < (int)sizeof(PPT_RECORD))
    {
        return;
    }

    int64 pos = 0;
    while(pos >= 0 && pos <= data_size - (int)sizeof(PPT_RECORD))
    {
        PPT_RECORD* header = (PPT_RECORD*)(data + pos);
        decodeText(text, (uint8*)header, data_size - pos);
        pos += sizeof(PPT_RECORD) + header->len;
    }
}

