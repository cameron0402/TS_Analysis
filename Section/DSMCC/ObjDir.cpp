#include "ObjDir.h"

Binding::Binding(uint8_t* data)
    : bname(NULL),
    iop_ior(NULL),
    binding_length(0)
{
    uint8_t* pd = data;

    bname = new BIOP_Name(pd);
    pd = data + bname->id_length + bname->kind_length + 3;
    binding_length += bname->id_length + bname->kind_length + 3;

    binding_type = pd[0];
    pd += 1;
    binding_length += 1;

    iop_ior = new IOP_IOR(pd);
    pd += iop_ior->iop_ior_length;
    binding_length += iop_ior->iop_ior_length;

    object_info_length = (pd[0] << 8) | pd[1];
    binding_length += 2 + object_info_length;
}

Binding::~Binding()
{
    if(bname != NULL)
        delete bname;
    if(iop_ior != NULL)
        delete iop_ior;
}

bool Binding::operator<(const Binding& bd)
{
    return (*(bd.iop_ior->biop_pf_list.begin()))->biop_objloc->object_key <
           (*(iop_ior->biop_pf_list.begin()))->biop_objloc->object_key;
}

bool Binding::operator==(const Binding& bd)
{
    return (*(bd.iop_ior->biop_pf_list.begin()))->biop_objloc->object_key ==
           (*(iop_ior->biop_pf_list.begin()))->biop_objloc->object_key;
}

ObjDir::ObjDir(uint8_t* data)
    : ObjDsmcc(data)
{
    uint8_t* pd = data + obj_length + object_info_length;
    obj_length += object_info_length;

    service_context_count = pd[0];
    obj_length += 1 + service_context_count;
    pd += 1 + service_context_count;

    message_body_length = (pd[0] << 24) | (pd[1] << 16) | (pd[2] << 8) | pd[3];
    binding_count = (pd[4] << 8) | pd[5];

    pd += 6;
    obj_length += 6;
    for(int i = 0; i < binding_count; ++i)
    {
        Binding* bd = new Binding(pd);
        binding_list.insert(bd);
        pd += bd->binding_length;
        obj_length += bd->binding_length;
    }
}

ObjDir::~ObjDir()
{
    std::set<Binding*, cmp_secp<Binding>>::iterator bit;
    for(bit = binding_list.begin(); bit != binding_list.end(); ++bit)
        delete (*bit);
    binding_list.clear();
}