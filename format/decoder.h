#ifndef __DECODER_H__
#define __DECODER_H__

#include "format.h"
#include "com_serializer.h"

#include "decoder_txt.h"
#include "decoder_open_xml.h"
#include "decoder_rtf.h"
#include "decoder_pdf.h"
#include "decoder_zip.h"
#include "decoder_archive.h"
#include "decoder_doc.h"
#include "decoder_ppt.h"
#include "decoder_xls.h"
#include "decoder_asar.h"

class FileDecoder
{
public:
    FileDecoder();
    virtual ~FileDecoder();

    template<class T>
    FormatResult decode(T path_or_content, std::string suffix = std::string())
    {
        std::string format_type = GetFormatTypeManager().detectFileFormat(path_or_content, suffix);
        if(format_type == "OpenXML")
        {
            FileDecoderOpenXML decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "PDF")
        {
            FileDecoderPdf decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "RTF")
        {
            FileDecoderRtf decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "ZIP")
        {
            FileDecoderZip decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "BZ2" || format_type == "GZ"
                || format_type == "XZ" || format_type == "7Z"
                || format_type == "RAR" || format_type == "ISO")
        {
            FileDecoderArchive decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "DOC")
        {
            FileDecoderDoc decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "PPT")
        {
            FileDecoderPpt decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "XLS")
        {
            FileDecoderXls decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "ASAR")
        {
            FileDecoderAsar decoder;
            return decoder.decode(path_or_content);
        }
        if(format_type == "TXT")
        {
            FileDecoderTxt decoder;
            return decoder.decode(path_or_content);
        }
        return FormatResult();
    }
};

FileDecoder& GetFileDecoder();

#endif /* __DECODER_H__ */

