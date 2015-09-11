#include "ObjFile.h"
#include "zconf.h"
#include "zlib.h"

ObjFile::ObjFile(uint8_t* data)
    : ObjDsmcc(data)
{
    uint8_t* pd = data + obj_length;
    content_size = (pd[0] << 56 | (pd[1] << 48) | (pd[2] << 40) | (pd[3] << 32) |
                    pd[4] << 24 | (pd[5] << 16) | (pd[6] << 8) | pd[7]);

    obj_length += object_info_length;
    pd += object_info_length;

    service_context_count = pd[0];
    pd += 1 + service_context_count;
    obj_length += 1 + service_context_count;

    message_body_size = (pd[0] << 24) | (pd[1] << 16) | (pd[2] << 8) | pd[3];
    file_length = (pd[4] << 24) | (pd[5] << 16) | (pd[6] << 8) | pd[7];
    real_file_length = file_length;

    file_content = new uint8_t[file_length];
    memcpy(file_content, pd + 8, file_length);

    obj_length += 8 + file_length;
}

ObjFile::~ObjFile()
{
    delete []file_content;
}


int ObjFile::uncompressObj()
{
    if(file_content == NULL)
        return -1;

    int res = Z_OK;
    const int MDL_COMPRESS_RATE = 0x50;
    unsigned long raw_file_size = file_length * MDL_COMPRESS_RATE;
    size_t bound_size = file_length * MDL_COMPRESS_RATE;
    uint8_t* com_buf = new uint8_t[bound_size];

    res = uncompress(com_buf, &raw_file_size, file_content, file_length);
    if(res == Z_OK)
    {
        delete file_content;
        file_content = new uint8_t[raw_file_size];
        memcpy(file_content, com_buf, raw_file_size);
        real_file_length = raw_file_size;
    }
    delete []com_buf;

    return res;
}