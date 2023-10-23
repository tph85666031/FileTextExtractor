#ifndef __DECODER_ARCHIVE_H__
#define __DECODER_ARCHIVE_H__

#include "format.h"

class FileDecoderArchive
{
public:
    FileDecoderArchive();
    virtual ~FileDecoderArchive();

    FormatResult decode(const char* file);
    FormatResult decode(const CPPBytes& content);
private:

};

#endif /* __DECODER_ARCHIVE_H__ */

