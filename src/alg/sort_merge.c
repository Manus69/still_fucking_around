#include "sort.h"
#include "./structure/Slice.h"
#include "../debug/debug.h"

static inline void _dump(Slice * restrict target, Slice * restrict src)
{
    Slice_set_many(target, 0, Slice_ptr(src), Slice_len(src));
    Slice_shift(target, Slice_len(src));
    Slice_shift(src, Slice_len(src));
}

static inline void _drop(Slice * restrict target, Slice * restrict src, Put put)
{
    Slice_set_ptr(target, 0, Slice_ptr(src), put);
    Slice_shift(target, 1);
    Slice_shift(src, 1);
}

static inline bool _is_sorted(const Slice * restrict lhs, const Slice * restrict rhs, Cmp cmp)
{
    return !Slice_empty(rhs) && (cmp(Slice_last(lhs), Slice_ptr(rhs)) < 0);
}

static inline void _merge(Slice * restrict target, 
                          Slice * restrict lhs, 
                          Slice * restrict rhs, 
                          Cmp cmp, 
                          Put put)
{
    while (true)
    {
        if (Slice_empty(rhs)) return _dump(target, lhs);
        if (Slice_empty(lhs)) return _dump(target, rhs);

        if (cmp(Slice_ptr(lhs), Slice_ptr(rhs)) > 0) _drop(target, rhs, put);
        else _drop(target, lhs, put);
    }
}

static inline void _pass(Slice * restrict target, 
                        Slice * restrict buffer, 
                        Cmp cmp, 
                        Put put, 
                        I32 frame_size)
{
    Slice lhs;
    Slice rhs;

    while (Slice_empty(buffer) == false)
    {
        lhs = Slice_chop_checked(buffer, frame_size);
        rhs = Slice_chop_checked(buffer, frame_size);

        _merge(target, & lhs, & rhs, cmp, put);
    }
}

static inline void _swap_buffers(Slice * restrict lhs, Slice * restrict rhs)
{
    mem_swap(& lhs->ptr, & rhs->ptr);
}

static inline Slice _get_buffer(I32 length, I32 item_size)
{
    return Slice_init(mem_allocate(length * item_size), item_size, length);
}

static inline void _check_swaps(Slice * restrict slice, Slice * restrict buffer, I32 n_swaps)
{
    if (n_swaps % 2)
    {
        _swap_buffers(slice, buffer);
        Slice_set_many(slice, 0, Slice_ptr(buffer), Slice_len(buffer));
    }
}

#define FRAME_SIZE (1 << 1)
static inline I32 _preprocess_insert(Slice * slice, Cmp cmp, Put put, Swap swap)
{
    Slice new_slice;
    Slice current;

    new_slice = Slice_to_Slice(slice);
    while (unlikely(Slice_empty(& new_slice) == false))
    {
        current = Slice_chop_checked(& new_slice, FRAME_SIZE);
        sort_insert(& current, cmp, put, swap);
    }

    return FRAME_SIZE;
}

static inline I32 _preprocess_swap(Slice * slice, Cmp cmp, Swap swap)
{
    I32     length;
    void *  lhs;
    void *  rhs;

    length = Slice_len(slice);

    for (I32 index = 1; index < length; index += 2)
    {
        lhs = Slice_get(slice, index - 1);
        rhs = Slice_get(slice, index);

        if (cmp(lhs, rhs) > 0) swap(lhs, rhs);
    }

    return 2;
}

void sort_merge(Slice * slice, Cmp cmp, Put put, Swap swap)
{
    Slice   buffer;
    I32     frame_size;
    I32     length;
    I32     n_swaps;

    length = Slice_len(slice);
    buffer = _get_buffer(length, Slice_item_size(slice));
    frame_size = _preprocess_swap(slice, cmp, swap);
    n_swaps = 0;

    while (frame_size <= length)
    {
        _pass(& buffer, slice, cmp, put, frame_size);

        Slice_shift(slice, - length);
        Slice_shift(& buffer, - length);
        _swap_buffers(slice, & buffer);
        n_swaps ++;
        frame_size <<= 1;
    }
    
    _check_swaps(slice, & buffer, n_swaps);
    mem_del(Slice_ptr(& buffer));
}
