#include "com_file.h"
#include "com_log.h"
#include "comex_archive.h"
#include "decoder.h"

FileDecoderArchive::FileDecoderArchive()
{
}

FileDecoderArchive::~FileDecoderArchive()
{
}

FormatResult FileDecoderArchive::decode(const char* file)
{
    FormatResult result;

    ArchiveReader reader(file);
    reader.list("*", [&](const std::string & file, int64 size)
    {
        LOG_I("size=%lld,%s", size, file.c_str());
        if(file.back() == '/' || size <= 0)
        {
            return;
        }
        CPPBytes data = reader.read();
        FormatResult ret = GetFileDecoder().decode(data, com_path_suffix(file.c_str()));
        result.text.append(ret.text);
        result.images.insert(result.images.end(), ret.images.begin(), ret.images.end());
    });

    return result;
}

FormatResult FileDecoderArchive::decode(const CPPBytes& content)
{
    FormatResult result;

    ArchiveReader reader(content.getData(), content.getDataSize());
    reader.list("*", [&](const std::string & file, int64 size)
    {
        LOG_I("size=%lld,%s", size, file.c_str());
        if(file.back() == '/' || size <= 0)
        {
            return;
        }
        CPPBytes data = reader.read();
        FormatResult ret = GetFileDecoder().decode(data, com_path_suffix(file.c_str()));
        result.text.append(ret.text);
        result.images.insert(result.images.end(), ret.images.begin(), ret.images.end());
    });

    return result;
}

