#include "ObjDsmcc.h"
#include "ObjDir.h"
#include "ObjFile.h"

ObjDsmcc::ObjDsmcc()
{

}

ObjDsmcc::ObjDsmcc(uint8_t* data)
    : version_major(data[4]),
      version_minor(data[5]),
      byte_order(data[6]),
      message_type(data[7]),
      message_size((data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11]),
      object_key_length(data[12]),
      object_kind_length((data[13 + object_key_length] << 24) | (data[14 + object_key_length] << 16) |
                         (data[15 + object_key_length] << 8) | (data[16 + object_key_length])),
      object_info_length(data[21 + object_key_length] << 8 | data[22 + object_key_length]),
      saved(false)
{
    memcpy(magic, data, 4);
    object_key = 0;
    for(int i = 0; i < object_key_length; ++i)
    {
        object_key <<= 8;
        object_key |= data[13 + i];
    }
    memcpy(object_kind, data + 17 + object_key_length, 4);

    obj_length = 23 + object_key_length;
}

ObjDsmcc::~ObjDsmcc()
{

}

bool ObjDsmcc::operator<(const ObjDsmcc& odc)
{
    return object_key < odc.object_key;
}

bool ObjDsmcc::operator==(const ObjDsmcc& odc)
{
    return object_key == odc.object_key;
}

int ObjDsmcc::uncompressObj()
{
    return -1;
}

ObjDsmcc* ObjFactory::createObj(uint8_t* data)
{
    uint8_t type[4];
    memcpy(type, data + 17 + data[12], 4);
    if((type[0] == 'd' && type[1] == 'i' && type[2] == 'r') ||
       (type[0] == 's' && type[1] == 'r' && type[2] == 'g'))
    {
        return new ObjDir(data);
    }
    else if(type[0] == 'f' && type[1] == 'i' && type[2] == 'l')
    {
        return new ObjFile(data);
    }

    return NULL;
}