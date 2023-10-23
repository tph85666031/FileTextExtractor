#ifndef __DECODER_OPEN_XML_H__
#define __DECODER_OPEN_XML_H__

#include "format.h"
#include "tinyxml2.h"
#include "comex_archive.h"

class FileDecoderOpenXML
{
public:
    FileDecoderOpenXML();
    virtual ~FileDecoderOpenXML();

    FormatResult decode(const char* file_path);
    FormatResult decode(const CPPBytes& content);
private:
    FormatResult parse(ArchiveZip& zip);
    std::string parseXmlText(const std::string& content);
    std::string parseXmlText(tinyxml2::XMLElement* node);
};

#endif /* __DECODER_OPEN_XML_H__ */

