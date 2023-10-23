#ifndef __DECODER_ASAR_H__
#define __DECODER_ASAR_H__

#include "com_serializer.h"
#include "format.h"

class AsarHeaderFileInfoIntegrity
{
public:
    std::string algorithm;
    std::string hash;
    int blockSize = 0;
    std::vector<std::string> blocks;
    META_J(algorithm, hash, blockSize, blocks);
};

class AsarHeaderFileInfo
{
public:
    std::string dir;
    std::string name;
    int size = 0;
    std::string offset;
    AsarHeaderFileInfoIntegrity integrity;
    META_J(dir, name, size, offset, integrity);
};

class FileDecoderAsar
{
public:
    FileDecoderAsar();
    virtual ~FileDecoderAsar();

    FormatResult decode(const char* file);
    FormatResult decode(const CPPBytes& content);
private:
    FormatResult parse(ByteStreamReader& bsr);
    void extractFileInfo(std::string dir, CJsonObject& obj);
    static uint32 LEtoHostOrder(uint32 val);
private:
    std::vector<AsarHeaderFileInfo> file_infos;
};

#endif /* __DECODER_ASAR_H__ */

