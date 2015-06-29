#include "ObjFile.h"

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
    content_length = (pd[4] << 24) | (pd[5] << 16) | (pd[6] << 8) | pd[7];

    file_content = new uint8_t[content_length];
    memcpy(file_content, pd + 8, content_length);

    obj_length += 8 + content_length;
}

ObjFile::~ObjFile()
{

}