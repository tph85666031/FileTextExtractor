#include "com_file.h"
#include "decoder_txt.h"

FileDecoderTxt::FileDecoderTxt()
{
}

FileDecoderTxt::~FileDecoderTxt()
{
}

FormatResult FileDecoderTxt::decode(const char* file)
{
    FormatResult result;
    result.text = com_file_readall(file);
    return result;
}

FormatResult FileDecoderTxt::decode(const CPPBytes& content)
{
    FormatResult result;
    result.text = content;
    return result;
}

