#ifndef __FORMAT_H__
#define __FORMAT_H__

#include "com_base.h"
#include "com_serializer.h"

class COM_EXPORT FormatType
{
public:
    std::string name;
    std::string description;
    uint32 priority = 0;
    int header_offset = 0;
    CPPBytes header;
    CPPBytes trailer;

    std::set<std::string> suffix;
    std::string group;

    bool operator<(const FormatType& right) const;

    META_J(name, description, priority, header, suffix, group, header_offset, trailer);
};

class COM_EXPORT FormatTypeManager
{
public:
    FormatTypeManager();
    virtual ~FormatTypeManager();

    void loadConfigFromFile(const char* file);
    void loadConfigFromContent(const CPPBytes& content);

    std::string detectFileFormat(const char* file, std::string suffix = std::string());
    std::string detectFileFormat(const CPPBytes& content, std::string suffix = std::string());

    std::vector<FormatType> types;
    META_J(types);
};

class COM_EXPORT FormatResult
{
public:
    bool valid = false;
    std::string file_path;
    CPPBytes text;
    std::vector<CPPBytes> images;
    Message params;
};

COM_EXPORT FormatTypeManager& GetFormatTypeManager();

#endif /* __FORMAT_H__ */

