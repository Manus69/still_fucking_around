#include "Vec.h"
#include <stdbool.h>

static inline bool _no_capacity(const Vec * vec)
{
    return Vec_remaining_capacity(vec) == 0;
}

static inline void _double_capacity(Vec * vec)
{
    Arr_extend(& vec->arr, vec->index);
}

void Vec_push_ptr(Vec * vec, const void * item, Put put)
{
    if (unlikely(_no_capacity(vec))) _double_capacity(vec);

    Vec_set_ptr(vec, vec->index ++, item, put);
}

void Vec_append_from_ptr(Vec * vec, const void * ptr, I32 n_items)
{
    Vec_reserve(vec, n_items);
    mem_copy(Vec_get(vec, vec->index), ptr, n_items, Vec_item_size(vec));
    vec->index += n_items;
}

void Vec_append_Slice(Vec * vec, const Slice * slice)
{
    Vec_append_from_ptr(vec, Slice_first(slice), Slice_len(slice));
}

void Vec_append_Vec(Vec * vec, const Vec * rhs)
{
    Slice slice;

    slice = Vec_to_Slice()
}

static inline void _shift_over(Vec * vec, I32 index)
{
    mem_move(Vec_get(vec, index), 
             Vec_get(vec, index + 1), 
             Vec_len(vec) - index - 1, 
             Vec_item_size(vec));
    
    vec->index --;
}

void Vec_remove_index(Vec * vec, I32 index)
{
    if (index == Vec_len(vec) - 1) return (void) Vec_pop(vec);

    _shift_over(vec, index);
}

void Vec_remove_index_buff(void * target, Vec * vec, I32 index, Put put)
{
    put(target, Vec_get(vec, index));
    Vec_remove_index(vec, index);
}

STATUS Vec_remove(Vec * vec, const void * item, Cmp cmp)
{
    I32 index;

    if ((index = Vec_find(vec, item, cmp)) == NO_INDEX) return STATUS_NOT_OK;
    Vec_remove_index(vec, index);

    return STATUS_OK;
}

STATUS Vec_remove_buff(void * target, Vec * vec, const void * item, Cmp cmp, Put put)
{
    I32 index;

    if ((index = Vec_find(vec, item, cmp)) == NO_INDEX) return STATUS_NOT_OK;
    Vec_remove_index_buff(target, vec, index, put);

    return STATUS_OK;
}