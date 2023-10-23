#include "com_file.h"
#include "com_log.h"
#include "comex_archive.h"
#include "decoder.h"

FileDecoderZip::FileDecoderZip()
{
}

FileDecoderZip::~FileDecoderZip()
{
}

FormatResult FileDecoderZip::decode(const char* file)
{
    ArchiveZip zip;
    zip.open(file);

    FormatResult result;

    std::vector<std::string> list = zip.getFileList();
    for(size_t i = 0; i < list.size(); i++)
    {
        if(list[i].back() == '/')
        {
            continue;
        }
        LOG_I("file=%s", list[i].c_str());
        CPPBytes data = zip.read(list[i].c_str());
        FormatResult tmp = GetFileDecoder().decode(data, com_path_suffix(list[i].c_str()));
        result.text.append(tmp.text);
        result.images.insert(result.images.end(), tmp.images.begin(), tmp.images.end());
    }

    return result;
}

FormatResult FileDecoderZip::decode(const CPPBytes& content)
{
    ArchiveZip zip;
    zip.open(content);

    FormatResult result;

    std::vector<std::string> list = zip.getFileList();
    for(size_t i = 0; i < list.size(); i++)
    {
        if(list[i].back() == '/')
        {
            continue;
        }
        CPPBytes data = zip.read(list[i].c_str());
        FormatResult tmp = GetFileDecoder().decode(data);
        result.text.append(tmp.text);
        result.images.insert(result.images.end(), tmp.images.begin(), tmp.images.end());
    }

    return result;
}

