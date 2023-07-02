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
    Arr arr;
    I32 index;
};

void Vec_push_ptr(Vec * vec, const void * item, Put put);
void Vec_remove_index(Vec * vec, I32 index);
void Vec_remove_index_buff(void * target, Vec * vec, I32 index, Put put);
STATUS Vec_remove(Vec * vec, const void * item, Cmp cmp);
STATUS Vec_remove_buff(void * target, Vec * vec, const void * item, Cmp cmp, Put put);

mem_put_gen(Vec)
mem_swap_gen(Vec)

static inline Vec Vec_init_capacity(I32 item_size, I32 capacity)
{
    assert(capacity > 0);

    return (Vec) {Arr_init(item_size, capacity), 0};
}

static inline Vec Vec_init(I32 item_size)
{
    return Vec_init_capacity(item_size, VEC_DC);
}

static inline Vec Vec_dup(const Vec * vec)
{
    return (Vec) {Arr_dup(& vec->arr), vec->index};
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

static inline I32 Vec_item_size(const Vec * vec)
{
    return Arr_item_size(& vec->arr);
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

static inline void Vec_extend_zero(Vec * vec, I32 n_items)
{
    Arr_extend_zero(& vec->arr, n_items);
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

static inline I32 Vec_find(const Vec * vec, const void * item, Cmp cmp)
{
    Slice slice;

    slice = Vec_to_Slice(vec);

    return Slice_find(& slice, item, cmp);
}

static inline bool Vec_contains(const Vec * vec, const void * item, Cmp cmp)
{
    return Vec_find(vec, item, cmp) != NO_INDEX;
}

static inline void * Vec_pop(Vec * vec)
{
    return Vec_get(vec, -- vec->index);
}

#endif