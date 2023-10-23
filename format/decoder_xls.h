#ifndef __DECODER_XLS_H__
#define __DECODER_XLS_H__

#include "format.h"

class FileDecoderXls
{
public:
    FileDecoderXls();
    virtual ~FileDecoderXls();

    FormatResult decode(const char* file_path);
    FormatResult decode(const CPPBytes& content);
};

#endif /* __DECODER_XLS_H__ */

