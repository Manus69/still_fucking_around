#ifndef VEC_H
#define VEC_H

#include "Arr.h"
#include "Slice.h"

#define VEC_DC (1 << 4)
#define Vec_init_t(type) Vec_init(sizeof(type))
#define Vec_set(vec_ptr, index, val) Arr_set(& ((vec_ptr)->arr), (index), (val))
#define Vec_push(vec_ptr, val, type) {type _t = val; Vec_push_ptr(vec_ptr, & _t, type##_put);}

typedef struct Vec Vec;

struct Vec
{
    I32 index;
    Arr arr;
};

void Vec_push_ptr(Vec * vec, const void * item, Put put);
mem_put_gen(Vec)
mem_swap_gen(Vec)

static inline Vec Vec_init_capacity(I32 item_size, I32 capacity)
{
    assert(capacity > 0);

    return (Vec) {0, Arr_init(item_size, capacity)};
}

static inline Vec Vec_init(I32 item_size)
{
    return Vec_init_capacity(item_size, VEC_DC);
}

static inline void Vec_del(Vec * vec)
{
    Arr_del(& vec->arr);
    * vec = (Vec) {0};
}

static inline void * Vec_get(const Vec * vec, I32 index)
{
    return Arr_get(& vec->arr, index);
}

static inline void Vec_set_ptr(Vec * vec, I32 index, const void * item, Put put)
{
    Arr_set_ptr(& vec->arr, index, item, put);
}

static inline I32 Vec_capacity(const Vec * vec)
{
    return Arr_len(& vec->arr);
}

static inline I32 Vec_len(const Vec * vec)
{
    return vec->index;
}

static inline I32 Vec_remaining_capacity(const Vec * vec)
{
    return Vec_capacity(vec) - Vec_len(vec);
}

static inline void * Vec_first(const Vec * vec)
{
    return Vec_get(vec, 0);
}

static inline void * Vec_last(const Vec * vec)
{
    return Vec_get(vec, Vec_len(vec) - 1);
}

static inline void Vec_reserve(Vec * vec, I32 n_items)
{
    if (n_items < Vec_remaining_capacity(vec)) return ;

    Arr_extend(& vec->arr, n_items);
}

static inline Slice Vec_slice(const Vec * vec, I32 index, I32 n_items)
{
    return Arr_slice(& vec->arr, index, n_items);
}

static inline Slice Vec_to_Slice(const Vec * vec)
{
    return Vec_slice(vec, 0, Vec_len(vec));
}

static inline void Vec_map(Vec * vec, F f)
{
    Slice slice;

    slice = Vec_to_Slice(vec);
    return Slice_map(& slice, f);
}

static inline void Vec_del_items(Vec * vec, F f)
{
    Vec_map(vec, f);
}

#endif