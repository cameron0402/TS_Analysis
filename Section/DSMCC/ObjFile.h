#ifndef _OBJ_FILE_H_
#define _OBJ_FILE_H_

#include "ObjDsmcc.h"

class ObjFile : public ObjDsmcc
{
public:
    ObjFile(uint8_t* data);
    virtual ~ObjFile();

    uint64_t content_size;
    //uint8_t* object_info;
    uint8_t service_context_count;
    //uint8_t* service_context_list;
    uint32_t message_body_size;
    uint32_t content_length;
    uint8_t* file_content;
};

#endif