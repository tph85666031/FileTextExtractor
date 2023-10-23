#ifndef __DECODER_TXT_H__
#define __DECODER_TXT_H__

#include "format.h"

class FileDecoderTxt
{
public:
    FileDecoderTxt();
    virtual ~FileDecoderTxt();

    FormatResult decode(const char* file);
    FormatResult decode(const CPPBytes& content);
private:

};

#endif /* __DECODER_TXT_H__ */

