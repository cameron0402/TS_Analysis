#ifndef SERVICELISTDESC_H_HEADER_INCLUDED_AAA61C15
#define SERVICELISTDESC_H_HEADER_INCLUDED_AAA61C15
#include "../Descriptor.h"

//descriptor_tag = 0x41
//##ModelId=5559822F0082
class ServiceListDesc : public Descriptor
{
  public:
    //##ModelId=5559824B0233
    class ServiceInfo
    {
      public:
        ServiceInfo();
        ServiceInfo(uint8_t* data);
        ~ServiceInfo();
        //##ModelId=5559825F027A
        uint16_t service_id;
        //##ModelId=5559827003C4
        uint8_t service_type;
    };

    //##ModelId=555982E400ED
    ServiceListDesc();

    //##ModelId=555982EF00FD
    ServiceListDesc(uint8_t* data);

    //##ModelId=5559831700ED
    virtual ~ServiceListDesc();

    virtual void resolved();

    //##ModelId=5559828B0375
    std::list<ServiceInfo*> service_list;
};



#endif /* SERVICELISTDESC_H_HEADER_INCLUDED_AAA61C15 */
