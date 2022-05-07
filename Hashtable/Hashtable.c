#include "Hashtable.h"

// amount of rows
static const uint16 HT_HEIGHTS[]={17,61,257,1021,4099,16381,65521};
#define HT_HEIN_MIN 0
#define HT_HEIN_MAX 6

#define ARR_BC 2
#define ARR_BL 8

Hashtable* Hashtable_create(){
    Hashtable* ht=malloc(sizeof(Hashtable));
    ht->hein=HT_HEIN_MIN;
    ht->rows=malloc(HT_HEIGHTS[HT_HEIN_MIN]*sizeof(Autoarr(KVPair)*));
    for(uint16 i=0;i<HT_HEIGHTS[HT_HEIN_MIN];i++)
        ht->rows[i]=Autoarr_create(KVPair,ARR_BC,ARR_BL);
    return ht;
}

void Hashtable_free(Hashtable* ht){
    for(uint16 i=0;i<HT_HEIGHTS[ht->hein];i++)
        Autoarr_free_KVPair(ht->rows[i]);
    free(ht->rows);
    free(ht);
}

uint16 Hashtable_height(Hashtable* ht) { return HT_HEIGHTS[ht->hein]; }


void Hashtable_expand(Hashtable* ht){
    if(ht->hein>=HT_HEIN_MAX) throw(ERR_MAXLENGTH);

    Autoarr(KVPair)** newrows=malloc(HT_HEIGHTS[++ht->hein]*sizeof(Autoarr(KVPair)*));
    for(uint16 i=0;i<HT_HEIGHTS[ht->hein];i++)
        newrows[i]=Autoarr_create(KVPair,ARR_BC,ARR_BL);

    for(uint16 i=0;i<HT_HEIGHTS[ht->hein-1];i++){
        Autoarr(KVPair)* ar=ht->rows[i];
        uint32 arlen=Autoarr_length(ar);
        for(uint16 k=0;k<arlen;k++){
            KVPair p=Autoarr_get(ar,k);
            uint16 newrown=hash32(p.key)%HT_HEIGHTS[ht->hein];
            Autoarr(KVPair)* newar=newrows[newrown];
            Autoarr_add(newar,p);
        }
        // it is a feature, not a bug
        // no need to free kvpair keys and values, they just moved to new autoarrs
        Autoarr_free(ar);
    }

    free(ht->rows);
    ht->rows=newrows;
}

Autoarr(KVPair)* getrow(Hashtable* ht, char* key, bool can_expand){
    uint32 hash=hash32(key);
    Autoarr(KVPair)* ar=ht->rows[hash%HT_HEIGHTS[ht->hein]];
    if(can_expand && Autoarr_length(ar)==Autoarr_max_length(ar))
        optime("expand",1,(Hashtable_expand(ht)));
    ar=ht->rows[hash%HT_HEIGHTS[ht->hein]];
    return ar;
}

void Hashtable_add(Hashtable* ht, char* key, Unitype u){
    KVPair p={ .key=key, .value=u };
    Autoarr_add(getrow(ht,key,true),p);
}

// returns null or pointer to value in hashtable
Unitype* Hashtable_getptr(Hashtable* ht, char* key){
    Autoarr(KVPair)* ar=getrow(ht,key,false);
    uint32 arlen=Autoarr_length(ar);
    for(uint32 i=0;i<arlen;i++){
        KVPair* p=Autoarr_getptr(ar,i);
        if(cptr_compare(key,p->key)) return &p->value;
    }
    return NULL;
}

Unitype Hashtable_get(Hashtable* ht, char* key){
    Autoarr(KVPair)* ar=getrow(ht,key,false);
    uint32 arlen=Autoarr_length(ar);
    for(uint32 i=0;i<arlen;i++){
        KVPair p=Autoarr_get(ar,i);
        if(cptr_compare(key,p.key)) return p.value;
    }
    return UniNull;
}

bool Hashtable_try_get(Hashtable* ht, char* key, Unitype* output){
    Unitype u=Hashtable_get(ht,key);
    *output=u;
    return u.type!=Null;
}

void Hashtable_addOrSet(Hashtable* ht, char* key, Unitype u){
    Unitype* val=Hashtable_getptr(ht, key);
    if(val) *val=u;
    else Hashtable_add(ht, key, u);
}
