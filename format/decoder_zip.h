#ifndef __DECODER_ZIP_H__
#define __DECODER_ZIP_H__

#include "format.h"

class FileDecoderZip
{
public:
    FileDecoderZip();
    virtual ~FileDecoderZip();

    FormatResult decode(const char* file);
    FormatResult decode(const CPPBytes& content);
private:

};

#endif /* __DECODER_ZIP_H__ */

