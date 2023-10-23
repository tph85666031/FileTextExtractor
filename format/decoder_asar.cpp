#include "com_log.h"
#include "com_file.h"
#include "comex_openssl.h"
#include "decoder_asar.h"
#include "decoder.h"

FileDecoderAsar::FileDecoderAsar()
{
}

FileDecoderAsar::~FileDecoderAsar()
{
}

FormatResult FileDecoderAsar::decode(const char* file)
{
    if(com_string_is_empty(file))
    {
        return FormatResult();
    }

    ByteStreamReader bsr(file, true);
    return parse(bsr);
}

FormatResult FileDecoderAsar::decode(const CPPBytes& content)
{
    ByteStreamReader bsr(content);

    return parse(bsr);
}

FormatResult FileDecoderAsar::parse(ByteStreamReader& bsr)
{
    CPPBytes bytes = bsr.read(4);
    if(bytes.empty())
    {
        return FormatResult();
    }

    //decode header size
    uint32 len = *((uint32*)bytes.getData());
    len = LEtoHostOrder(len);
    if(len <= 0)
    {
        return FormatResult();
    }
    LOG_I("len=%u,%s", len, bytes.toHexString().c_str());

    bytes = bsr.read(len);
    if(bytes.empty())
    {
        return FormatResult();
    }
    uint32 header_size = *((uint32*)bytes.getData());
    header_size = LEtoHostOrder(header_size);
    if(header_size <= 0)
    {
        return FormatResult();
    }
    LOG_I("header_size=%u", header_size);

    //decode header(it's string)
    bytes = bsr.read(4);
    if(bytes.empty())
    {
        return FormatResult();
    }
    len = *((uint32*)bytes.getData());
    len = LEtoHostOrder(len);
    if(len <= 0)
    {
        return FormatResult();
    }
    LOG_I("len=%u", len);

    //decode json string size
    bytes = bsr.read(4);
    if(bytes.empty())
    {
        return FormatResult();
    }
    uint32 json_len = *((uint32*)bytes.getData());
    json_len = LEtoHostOrder(json_len);
    if(json_len <= 0)
    {
        return FormatResult();
    }
    LOG_I("json_len=%u", json_len);

    std::string header_json = bsr.read(json_len).toString();
    //LOG_I("json=%s", header_json.c_str());

    CJsonObject obj;
    obj.Parse(header_json);
    extractFileInfo("", obj["files"]);
    int64 offset = header_size + 8;

    FormatResult result;
    for(size_t i = 0; i < file_infos.size(); i++)
    {
        AsarHeaderFileInfo& info = file_infos[i];
        std::string suffix = com_path_suffix(info.name.c_str());

        bsr.setPos(offset + strtol(info.offset.c_str(), NULL, 10));
        CPPBytes content = bsr.read(info.size);
        //content.toFile(com_string_format("./gg/%s/%s", info.dir.c_str(), info.name.c_str()).c_str());

        std::string hash = OpensslHash::Digest(info.integrity.algorithm.c_str(), content.getData(), content.getDataSize()).toHexString(false);
        if(com_string_equal_ignore_case(hash.c_str(), info.integrity.hash.c_str()))
        {
            FormatResult ret = GetFileDecoder().decode(content, suffix);
            result.text.append(ret.text);
            result.images.insert(result.images.end(), ret.images.begin(), ret.images.end());
        }
    }

    return result;
}

void FileDecoderAsar::extractFileInfo(std::string dir, CJsonObject& obj)
{
    std::string key;
    while(obj.GetKey(key))
    {
        CJsonObject obj_sub;
        obj.Get(key, obj_sub);

        AsarHeaderFileInfo info;
        info.fromJson(obj_sub.ToString().c_str());
        if(info.size == 0)
        {
            std::string dir_sub = dir.empty() ? key : (dir + "/" + key);
            extractFileInfo(dir_sub, obj_sub["files"]);
        }
        else
        {
            info.dir = dir;
            info.name = key;
            file_infos.push_back(info);
        }
    }
}

uint32 FileDecoderAsar::LEtoHostOrder(uint32 val)
{
    if(htons(0x1234) == 0x1234)
    {
        return ((val & 0xff000000u) >> 24) | ((val & 0x00ff0000u) >> 8) | ((val & 0x0000ff00u) << 8) | ((val & 0x000000ffu) << 24);
    }
    else
    {
        return val;
    }
}

