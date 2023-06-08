#include "../../kprint/kprint_format.h"
#include "../base.h"

char *__Unitype_toString(allocator_ptr al, void *_u, u32 fmt)
{
    return Unitype_toString(al, *(Unitype *)_u, fmt);
}

kt_define(Unitype, (freeMembers_t)Unitype_destruct, __Unitype_toString);

void Unitype_destruct(Unitype* u)
{
    if (u->typeId == ktid_undefined)
    {
        if (u->VoidPtr != NULL)
            throw("unitype with undefined typeId has value");
        return;
    }

    ktDescriptor *type = ktDescriptor_get(u->typeId);
    if (type->freeMembers)
        type->freeMembers(u->VoidPtr);
    if (u->allocatedInHeap)
        free(u->VoidPtr);
}

char *Unitype_toString(allocator_ptr al, Unitype u, u32 fmt)
{
    if (u.typeId == ktid_undefined)
    {
        if (u.VoidPtr != NULL)
            throw("unitype with undefined typeId has value");
        return cptr_copy(al, "{ERROR_TYPE}");
    }

    if (fmt == 0)
    {
        if (u.typeId == ktid_name(bool) || u.typeId == ktid_name(i8) || u.typeId == ktid_name(i16) ||
            u.typeId == ktid_name(i32) || u.typeId == ktid_name(i64))
        {
            // auto format set
            fmt = kp_i;
            // replaces value with pointer to value to pass into toString_i64(void*, u32)
            i64 value = u.Int64;
            u.VoidPtr = &value;
        }
        else if (u.typeId == ktid_name(u8) || u.typeId == ktid_name(u16) || u.typeId == ktid_name(u32) ||
                 u.typeId == ktid_name(u64))
        {
            fmt = kp_u;
            u64 value = u.UInt64;
            u.VoidPtr = &value;
        }
        else if (u.typeId == ktid_name(f32) || u.typeId == ktid_name(f64))
        {
            fmt = kp_f;
            f64 value = u.Float64;
            u.VoidPtr = &value;
        }
        else if (u.typeId == ktid_name(char))
        {
            fmt = kp_c;
            i64 value = u.Int64;
            u.VoidPtr = &value;
        }
        else if (u.typeId == ktid_ptrName(char))
        {
            fmt = kp_s;
        }
        else if (u.typeId == ktid_name(Pointer))
        {
            if (u.VoidPtr == NULL)
                return cptr_copy(al, "{ UniNull }");
            fmt = kp_h;
        }
    }

    ktDescriptor *type = ktDescriptor_get(u.typeId);
    char *valuestr;
    if (type->toString)
        valuestr = type->toString(al, u.VoidPtr, fmt);
    else
        valuestr = "ERR_NO_TOSTRING_FUNC";
    char *rezult = cptr_concat(al, "{ type: ", type->name, ", allocated on heap: ", (u.allocatedInHeap ? "true" : "false"),
                               ", value:", valuestr, " }");
    if (type->toString)
        allocator_free(al, valuestr);
    return rezult;
}

void printuni(Unitype v)
{
    LinearAllocator _al;
    LinearAllocator_construct(&_al, 256);
    allocator_ptr al=&_al.base;
    char *s = Unitype_toString(al, v, 0);
    fputs(s, stdout);
    LinearAllocator_destruct(&_al);
}
