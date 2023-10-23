#include "com_file.h"
#include "com_log.h"
#include "com_xml.h"
#include "decoder.h"
#include "decoder_open_xml.h"

using namespace tinyxml2;

FileDecoderOpenXML::FileDecoderOpenXML()
{
}

FileDecoderOpenXML::~FileDecoderOpenXML()
{
}

FormatResult FileDecoderOpenXML::decode(const char* file_path)
{
    ArchiveZip zip;
    zip.open(file_path, false, false);

    FormatResult result = parse(zip);
    result.params.set("file", file_path);
    return result;
}

FormatResult FileDecoderOpenXML::decode(const CPPBytes& content)
{
    ArchiveZip zip;
    zip.open(content);

    return parse(zip);
}


FormatResult FileDecoderOpenXML::parse(ArchiveZip& zip)
{
    FormatResult result;

    std::vector<std::string> list = zip.getFileList();
    for(size_t i = 0; i < list.size(); i++)
    {
        if(list[i].back() == '/')
        {
            continue;
        }

        CPPBytes data = zip.read(list[i].c_str());
        if(data.empty())
        {
            continue;
        }

        if(com_string_start_with(list[i].c_str(), "media/"))
        {
            result.images.push_back(data);
        }
        else if(com_string_end_with(list[i].c_str(), ".xml"))
        {
            if(list[i] == "docProps/app.xml")
            {
                CPPXmlParser xml(data);
                result.params.set("template", xml.getText("Properties/Template"));
                result.params.set("words", xml.getText("Properties/Words"));
                result.params.set("characters", xml.getText("Properties/Characters"));
                result.params.set("pages", xml.getText("Properties/Pages"));
                result.params.set("app", xml.getText("Properties/Application"));
            }
            else if(list[i] == "docProps/core.xml")
            {
                CPPXmlParser xml(data);
                result.params.set("creator", xml.getText("cp:coreProperties/dc:creator"));
                result.params.set("editor", xml.getText("cp:coreProperties/cp:lastModifiedBy"));
                result.params.set("create_time", xml.getText("cp:coreProperties/dcterms:created"));
                result.params.set("modify_time", xml.getText("cp:coreProperties/dcterms:modified"));
            }
            result.text.append(parseXmlText(data.toString()).c_str());
        }
    }

    return result;
}

std::string FileDecoderOpenXML::parseXmlText(const std::string& content)
{
    XMLDocument doc;
    doc.Parse(content.c_str(), content.length());
    return parseXmlText(doc.RootElement());
}

std::string FileDecoderOpenXML::parseXmlText(XMLElement* node)
{
    std::string result;
    if(node == NULL)
    {
        return std::string();
    }
    while(node != NULL)
    {
        const char* text = node->GetText();
        if(text != NULL)
        {
            result.append(text);
            if(result.back() != '\n')
            {
                result.append("\n");
            }
        }
        result.append(parseXmlText(node->FirstChildElement()));
        node = node->NextSiblingElement();
    }
    return result;
}

