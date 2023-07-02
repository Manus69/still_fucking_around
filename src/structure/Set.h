#ifndef SET_H
#define SET_H

#include "Arr.h"
#include "Vec.h"

#define SET_DVC (1 << 2)
#define SET_DC  (1 << 4)

#define Set_init_t(type) Set_init(sizeof(type), SET_DC)
#define Set_insert(set_ptr, ptr, type) Set_insert_ptr(set_ptr, ptr, type##_hash, type##_cmp, type##_put)
#define Set_insert_val(set_ptr, val, type) \
{type _t = val; Set_insert(set_ptr, & _t, type);}

typedef struct Set Set;

struct Set
{
    Arr buckets;
    I32 n_items;
};

void * Set_get(const Set * set, const void * item, Hash hash, Cmp cmp);
STATUS Set_remove_ptr_buff(void * target, 
                           Set * set, 
                           const void * item, 
                           Hash hash, 
                           Cmp cmp, 
                           Put put);
STATUS Set_remove(Set * set, const void * item, Hash hash, Cmp cmp);
void Set_del(Set * set);
void Set_map(Set * set, F f);
void Set_del_items(Set * set, F f);
STATUS Set_insert_ptr(Set * set, const void * item, Hash hash, Cmp cmp, Put put);
void Set_insert_Slice(Set * set, const Slice * slice, Hash hash, Cmp cmp, Put put);
void Set_insert_Vec(Set * set, const Vec * vec, Hash hash, Cmp cmp, Put put);

static inline Set Set_init(I32 item_size, I32 capacity)
{
    Set set;

    set = (Set) {Arr_init(sizeof(Vec), capacity), 0};
    for (I32 k = 0; k < capacity; k ++)
    {
        deref(Vec) Arr_get(& set.buckets, k) = Vec_init_capacity(item_size, SET_DVC);
    }

    return set;
}

static inline I32 Set_n_items(const Set * set)
{
    return set->n_items;
}

static inline bool Set_contains(const Set * set, const void * item, Hash hash, Cmp cmp)
{
    return Set_get(set, item, hash, cmp);
}

static inline bool Set_empty(const Set * set)
{
    return Set_n_items(set) == 0;
}

static inline I32 Set_item_size(const Set * set)
{
    return Vec_item_size(Arr_get(& set->buckets, 0));
}

#endif