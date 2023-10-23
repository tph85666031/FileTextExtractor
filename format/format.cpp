#include "com_file.h"
#include "com_log.h"
#include "format.h"

FormatTypeManager& GetFormatTypeManager()
{
    static FormatTypeManager manager;
    return manager;
}

bool FormatType::operator<(const FormatType& right) const
{
    return priority > right.priority;
}

FormatTypeManager::FormatTypeManager()
{
}

FormatTypeManager::~FormatTypeManager()
{
}

void FormatTypeManager::loadConfigFromFile(const char* file)
{
    if(file == NULL)
    {
        LOG_E("arg incorrect");
        return;
    }
    fromJson(com_file_readall(file).toString().c_str());
}

void FormatTypeManager::loadConfigFromContent(const CPPBytes& content)
{
    fromJson(content.toString().c_str());
}

std::string FormatTypeManager::detectFileFormat(const char* file, std::string suffix)
{
    FILE* fp = com_file_open(file, "rb");
    if(fp == NULL)
    {
        return std::string();
    }
    CPPBytes header;
    CPPBytes trailer;

    std::set<FormatType> results;
    if(suffix.empty())
    {
        suffix = com_path_suffix(file);
    }
    com_string_to_upper(suffix);
    for(size_t i = 0; i < types.size(); i++)
    {
        FormatType type = types[i];
        if(type.header_offset < 0)
        {
            type.header_offset = 0;
        }
        if(header.getDataSize() < type.header.getDataSize() + type.header_offset)
        {
            com_file_seek_head(fp);
            header = com_file_read(fp, type.header.getDataSize() + type.header_offset);
        }

        if(header.getDataSize() < type.header.getDataSize() + type.header_offset)
        {
            continue;
        }

        if(trailer.getDataSize() < type.trailer.getDataSize())
        {
            com_file_seek_set(fp, -1 * type.trailer.getDataSize());
            trailer = com_file_read(fp, type.trailer.getDataSize());
        }

        if(trailer.getDataSize() < type.trailer.getDataSize())
        {
            continue;
        }

        uint8* p_header = header.getData() + type.header_offset;
        uint8* p_trailer = trailer.getData() + trailer.getDataSize() - type.trailer.getDataSize();

        if(memcmp(p_header, type.header.getData(), type.header.getDataSize()) != 0
                || memcmp(p_trailer, type.trailer.getData(), type.trailer.getDataSize()) != 0)
        {
            continue;
        }

        if(type.suffix.count(suffix))
        {
            type.priority |= 0x80000000;
        }
        results.insert(type);
    }

    com_file_close(fp);
    if(results.empty())
    {
        return std::string();
    }

    return results.begin()->name;
}

std::string FormatTypeManager::detectFileFormat(const CPPBytes& content, std::string suffix)
{
    std::set<FormatType> results;
    com_string_to_upper(suffix);
    for(size_t i = 0; i < types.size(); i++)
    {
        FormatType type = types[i];
        if(type.header_offset < 0)
        {
            type.header_offset = 0;
        }

        if(content.getDataSize() < type.header.getDataSize() + type.header_offset + type.trailer.getDataSize())
        {
            continue;
        }

        const uint8* p_header = content.getData() + type.header_offset;
        const uint8* p_trailer = content.getData() + content.getDataSize() - type.trailer.getDataSize();
        if(memcmp(p_header, type.header.getData(), type.header.getDataSize()) != 0
                || memcmp(p_trailer, type.trailer.getData(), type.trailer.getDataSize()) != 0)
        {
            continue;
        }

        if(type.suffix.count(suffix))
        {
            type.priority |= 0x80000000;
        }
        results.insert(type);
    }

    if(results.empty())
    {
        return std::string();
    }

    return results.begin()->name;
}

