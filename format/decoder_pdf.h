#ifndef __DECODER_PDF_H__
#define __DECODER_PDF_H__

#include "com_base.h"
#include "format.h"

class FileDecoderPdf
{
public:
    FileDecoderPdf();
    virtual ~FileDecoderPdf();

    FormatResult decode(const char* file_path);
    FormatResult decode(const CPPBytes& content);
};

#endif /* __DECODER_PDF_H__ */

