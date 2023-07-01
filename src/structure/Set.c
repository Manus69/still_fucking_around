#include "Set.h"

#define SET_DENSITY_THRESHOLD (3)

static inline U64 _n_buckets(const Set * set)
{
    return Arr_len(& set->buckets);
}

static inline I32 _bucket_index(const Set * set, const void * item, Hash hash)
{
    return hash(item) % _n_buckets(set);
}

static inline Vec * _bucket(const Set * set, const void * item, Hash hash)
{
    return Arr_get(& set->buckets, _bucket_index(set, item, hash));
}

void * Set_get(const Set * set, const void * item, Hash hash, Cmp cmp)
{
    Vec *   bucket;
    I32     index;

    bucket = _bucket(set, item, hash);
    index = Vec_find(bucket, item, cmp);

    return index == NO_INDEX ? NULL : Vec_get(bucket, index);
}

static inline void _rehash(Set * restrict target, const Set * restrict src, Hash hash, Cmp cmp, Put put)
{
    I32 n_buckets;

    n_buckets = _n_buckets(src);
    for (I32 k = 0; k < n_buckets; k ++)
    {
        Set_insert_Vec(target, Arr_get(& target->buckets, k), hash, cmp, put);
    }
}

STATUS Set_insert_ptr(Set * set, const void * item, Hash hash, Cmp cmp, Put put)
{
    Vec * bucket;
    
    bucket = _bucket(set, item, hash);
    if (Vec_contains(bucket, item, cmp)) return STATUS_NOT_OK;

    Vec_push_ptr(bucket, item, put);
    set->n_items ++;

    return STATUS_OK;
}

void Set_insert_Slice(Set * set, const Slice * slice, Hash hash, Cmp cmp, Put put)
{
    I32 len;

    len = Slice_len(slice);
    for (I32 k = 0; k < len; k ++)
    {
        Set_insert_ptr(set, Slice_get(slice, k), hash, cmp, put);
    }
}

void Set_insert_Vec(Set * set, const Vec * vec, Hash hash, Cmp cmp, Put put)
{
    Slice slice;

    slice = Vec_to_Slice(vec);
    Set_insert_Slice(set, & slice, hash, cmp, put);
}

STATUS Set_remove_ptr_buff(void * target, 
                           Set * set, 
                           const void * item, 
                           Hash hash, 
                           Cmp cmp, 
                           Put put)
{
    Vec *   bucket;
    I32     index;

    bucket = _bucket(set, item, hash);
    index = Vec_find(bucket, item, cmp);

    if (index == NO_INDEX) return STATUS_NOT_OK;

    Vec_remove_buff(target, bucket, item, cmp, put);
    set->n_items --;

    return STATUS_OK;
}

STATUS Set_remove(Set * set, const void * item, Hash hash, Cmp cmp)
{
    Vec * bucket;

    bucket = _bucket(set, item, hash);

    if (Vec_remove(bucket, item, cmp) == STATUS_OK)
    {
        set->n_items --;
        return STATUS_OK;
    }

    return STATUS_NOT_OK;
}

void Set_del(Set * set)
{
    Arr_del_items(& set->buckets, (F) Vec_del);
    Arr_del(& set->buckets);
    * set = (Set) {0};
}

void Set_map(Set * set, F f)
{
    I32 n_buckets;

    n_buckets = _n_buckets(set);
    for (I32 k = 0; k < n_buckets; k ++)
    {
        Vec_map(Arr_get(& set->buckets, k), f);
    }
}

void Set_del_items(Set * set, F f)
{
    Set_map(set, f);
}
