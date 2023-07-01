#ifndef ARR_H
#define ARR_H

#include "../core/mem.h"
#include "Block.h"
#include "Slice.h"

#define Arr_init_t(type, length) Arr_init(sizeof(type), length)
#define Arr_set(arr_ptr, index, val) mem_put_val(Arr_get(arr_ptr, index), (val))

typedef struct Arr Arr;

struct Arr
{
    I32     item_size;
    Block   block;
};

mem_put_gen(Arr)
mem_swap_gen(Arr)

static inline Arr Arr_init(I32 item_size, I32 length)
{
    return (Arr) {item_size, Block_init(length * item_size)};
}

static inline void Arr_del(Arr * arr)
{
    Block_del(& arr->block);
    * arr = (Arr) {0};
}

static inline I32 Arr_len(const Arr * arr)
{
    return Block_size(& arr->block) / arr->item_size;
}

static inline I32 Arr_item_size(const Arr * arr)
{
    return arr->item_size;
}

static inline void * Arr_get(const Arr * arr, I32 index)
{
    return Block_get(& arr->block, index * arr->item_size);
}

static inline void Arr_set_ptr(Arr * arr, I32 index, const void * item, Put put)
{
    put(Arr_get(arr, index), item);
}

static inline void Arr_extend(Arr * arr, I32 n_items)
{
    Block_extend(& arr->block, n_items * arr->item_size);
}

static inline Slice Arr_slice(const Arr * arr, I32 index, I32 n_items)
{
    return Slice_init(Arr_get(arr, index), Arr_item_size(arr), n_items);
}

static inline Slice Arr_to_Slice(const Arr * arr)
{
    return Arr_slice(arr, 0, Arr_len(arr));
}

static inline void Arr_map(Arr * arr, F f)
{
    Slice slice;

    slice = Arr_to_Slice(arr);

    return Slice_map(& slice, f);
}

static inline void Arr_del_items(Arr * arr, F f)
{
    Arr_map(arr, f);
}

#endif