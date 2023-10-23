#ifndef __DECODER_PPT_H__
#define __DECODER_PPT_H__

#include "format.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint16 ver: 4;
    uint16 instance: 12;
    uint16 type;
    uint32 len;
    uint8 data[0];
} PPT_RECORD;
#pragma pack(pop)

class FileDecoderPpt
{
public:
    FileDecoderPpt();
    virtual ~FileDecoderPpt();

    FormatResult decode(const char* file_path);
    FormatResult decode(const CPPBytes& content);

private:
    void decodeText(CPPBytes& text, const uint8* data, int data_size);
    void decodeTextArray(CPPBytes& text, const uint8* data, int data_size);
};

#endif /* __DECODER_PPT_H__ */

