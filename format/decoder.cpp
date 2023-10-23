#include "com_file.h"
#include "com_log.h"
#include "decoder.h"

FileDecoder& GetFileDecoder()
{
    static FileDecoder decoder;
    return decoder;
}

FileDecoder::FileDecoder()
{
}

FileDecoder::~FileDecoder()
{
}

