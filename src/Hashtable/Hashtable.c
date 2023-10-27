#include "Hashtable.h"

kt_define(Hashtable, __Hashtable_destruct, NULL);

// amount of rows
static const u16 HT_HEIGHTS[]={17,61,257,1021,4099,16381,65521};
#define HT_HEIN_MIN 0
#define HT_HEIN_MAX 6

#define ARR_SIZE_MAX 16

void Hashtable_construct(Hashtable* ht, allocator_ptr external_al){
    InternalAllocator_setExternalOrConstruct(ht, external_al, LinearAllocator, 1024);
    ht->hein=HT_HEIN_MIN;
    ht->rows=malloc(HT_HEIGHTS[HT_HEIN_MIN]*sizeof(Autoarr(KVPair)*));
    allocator_ptr internal_al = InternalAllocator_getPtr(ht);
    for(u16 i=0; i<HT_HEIGHTS[HT_HEIN_MIN]; i++)
        Autoarr_construct(&ht->rows[i], KVPair, 16, internal_al);
}

u16 __Hashtable_height(Hashtable* ht) { return HT_HEIGHTS[ht->hein]; }

void __Hashtable_destruct(void* _ht){
    Hashtable* ht=_ht;
    for(u16 i=0;i<HT_HEIGHTS[ht->hein];i++)
        Autoarr_destruct(&ht->rows[i]);
    allocator_free(InternalAllocator_getPtr(ht), ht->rows);
    InternalAllocator_destructIfInternal(LinearAllocator, ht);
}
void Hashtable_destruct(Hashtable* ht){
    __Hashtable_destruct(ht);
}

void Hashtable_expand(Hashtable* ht){
    if(ht->hein>=HT_HEIN_MAX) throw(ERR_MAXLENGTH);

    Autoarr(KVPair)* newrows=malloc(HT_HEIGHTS[++ht->hein]*sizeof(Autoarr(KVPair)*));
    for(u16 i=0;i<HT_HEIGHTS[ht->hein];i++)
        Autoarr_construct(&newrows[i], KVPair, ARR_SIZE_MAX, InternalAllocator_getPtr(ht));

    for(u16 i=0;i<HT_HEIGHTS[ht->hein-1];i++){
        Autoarr(KVPair)* ar=&ht->rows[i];
        u32 arlen=Autoarr_length(ar);
        for(u32 k=0;k<arlen;k++){
            KVPair p=Autoarr_get(ar,k);
            u16 newrown=hashs(hash_sdbm32, p.key)%HT_HEIGHTS[ht->hein];
            Autoarr(KVPair)* newar=&newrows[newrown];
            Autoarr_add(newar,p);
        }
        Autoarr_destruct(ar);
    }

    free(ht->rows);
    ht->rows = newrows;
}

Autoarr(KVPair)* getrow(Hashtable* ht, char* key, bool can_expand){
    u32 hash=hashs(hash_sdbm32, key);
    Autoarr(KVPair)* ar=&ht->rows[hash%HT_HEIGHTS[ht->hein]];
    if(can_expand && Autoarr_length(ar) == ARR_SIZE_MAX)
        Hashtable_expand(ht);
    ar=&ht->rows[hash%HT_HEIGHTS[ht->hein]];
    return ar;
}

/// @param key must be heap allocated
/// Hashtable_destruct will free this pointer
void Hashtable_add(Hashtable* ht, char* key, Unitype u){
    KVPair p={ .key=key, .value=u };
    Autoarr_add(getrow(ht,key,true),p);
}

void Hashtable_addMany(Hashtable* ht, KVPair* pair_array, u32 count){
    for(u32 i=0; i<count; i++){
        Hashtable_add(ht, pair_array[i].key, pair_array[i].value);
    }
}

// returns null or pointer to value in hashtable
Unitype* Hashtable_getPtr(Hashtable* ht, char* key){
    Autoarr(KVPair)* ar=getrow(ht,key,false);
    u32 arlen=Autoarr_length(ar);
    for(u32 i=0;i<arlen;i++){
        KVPair* p=Autoarr_getPtr(ar,i);
        if(cptr_equals(key,p->key))
            return &p->value;
    }
    return NULL;
}

Unitype Hashtable_get(Hashtable* ht, char* key){
    Autoarr(KVPair)* ar=getrow(ht,key,false);
    u32 arlen=Autoarr_length(ar);
    for(u32 i=0;i<arlen;i++){
        KVPair p=Autoarr_get(ar,i);
        if(cptr_equals(key,p.key))
            return p.value;
    }
    return UniNull;
}

bool Hashtable_tryGet(Hashtable* ht, char* key, Unitype* output){
    Unitype u=Hashtable_get(ht,key);
    *output=u;
    return !Unitype_isUniNull(u);
}


bool Hashtable_trySet(Hashtable* ht, char* key, Unitype u){
    Unitype* val=Hashtable_getPtr(ht,key);
    if(val==NULL)
        return false;
    *val=u;
    return true;
}

bool Hashtable_tryAdd(Hashtable* ht, char* key, Unitype u){
    Unitype* val=Hashtable_getPtr(ht,key);
    if(val==NULL){
        Hashtable_add(ht, key, u);
        return true;
    }
    return false;
}

void Hashtable_addOrSet(Hashtable* ht, char* key, Unitype u){
    Unitype* val=Hashtable_getPtr(ht, key);
    if(val==NULL)
        Hashtable_add(ht, key, u); // add
    else *val=u;   // set
}
