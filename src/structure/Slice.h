#ifndef SLICE_H
#define SLICE_H

#include "./core/mem.h"

#define Slice_init_t(ptr, n_items, type) Slice_init(ptr, sizeof(type), n_items)

typedef struct Slice Slice;

struct Slice
{
    void *  ptr;
    I32     item_size;
    I32     n_items;
};

mem_swap_gen(Slice)
mem_put_gen(Slice)

static inline Slice Slice_init(void * ptr, I32 item_size, I32 n_items)
{
    return (Slice) {ptr, item_size, n_items};
}

static inline void * Slice_get(const Slice * slice, I32 index)
{
    return slice->ptr + index * slice->item_size;
}

static inline void Slice_set_ptr(Slice * slice, I32 index, const void * item, Put put)
{
    put(Slice_get(slice, index), item);
}

static inline I32 Slice_item_size(const Slice * slice)
{
    return slice->item_size;
}

static inline void Slice_set_many(Slice * slice, I32 index, const void * ptr, I32 n_items)
{
    mem_copy(Slice_get(slice, index), ptr, n_items, Slice_item_size(slice));
}

static inline void * Slice_ptr(const Slice * slice)
{
    return Slice_get(slice, 0);
}

static inline I32 Slice_len(const Slice * slice)
{
    return slice->n_items;
}

static inline void * Slice_first(const Slice * slice)
{
    return Slice_get(slice, 0);
}

static inline void * Slice_last(const Slice * slice)
{
    return Slice_get(slice, Slice_len(slice) - 1);
}

static inline bool Slice_empty(const Slice * slice)
{
    return Slice_len(slice) == 0;
}

static inline void Slice_shift(Slice * slice, I32 n_items)
{
    slice->ptr = Slice_get(slice, n_items);
    slice->n_items -= n_items;
}

static inline void Slice_shrink(Slice * slice, I32 n_items)
{
    slice->n_items -= n_items;
}

static inline I32 Slice_find(const Slice * slice, const void * item, Cmp cmp)
{
    I32 length;

    length = Slice_len(slice);
    for (I32 k = 0; k < length; k ++)
    {
        if (equal(Slice_get(slice, k), item, cmp)) return k;
    }

    return NO_INDEX;
}

static inline void Slice_map(Slice * slice, F f)
{
    mem_map(Slice_ptr(slice), Slice_len(slice), Slice_item_size(slice), f);
}

static inline Slice Slice_slice(const Slice * slice, I32 index, I32 n_items)
{
    return Slice_init(Slice_get(slice, index), Slice_item_size(slice), n_items);
}

static inline Slice Slice_to_Slice(const Slice * slice)
{
    return Slice_slice(slice, 0, Slice_len(slice));
}

static inline Slice Slice_chop(Slice * slice, I32 len)
{
    Slice _slice;

    _slice = Slice_slice(slice, 0, len);
    Slice_shift(slice, len);

    return _slice;
}

static inline Slice Slice_chop_all(Slice * slice)
{
    return Slice_chop(slice, Slice_len(slice));
}

static inline Slice Slice_chop_checked(Slice * slice, I32 len)
{
    return len < Slice_len(slice) ? Slice_chop(slice, len) : Slice_chop_all(slice);
}

static inline void Slice_rev(Slice * slice, Swap swap)
{
    I32 mid;
    I32 length;

    length = Slice_len(slice);
    mid = Slice_len(slice) / 2;
    
    for (I32 k = 0; k < mid; k ++)
    {
        swap(Slice_get(slice, k), Slice_get(slice, length - k - 1));
    }
}

#endif