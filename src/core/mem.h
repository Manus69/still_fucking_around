#ifndef MEM_H
#define MEM_H

#include "def.h"
#include "macro.h"

#include <assert.h>
#include <string.h>

void mem_vmap(F f, ...);

static inline void * mem_point(const void * ptr, I32 index, I32 item_size)
{
    return (void *)(ptr + (index * item_size));
}

#define mem_put_val(ptr, val) deref(typeof(val)) ptr = val

#define mem_swap_t(lhs, rhs, type) \
{ \
    type _t = deref(type) (lhs); \
    deref(type) (lhs) = deref(type) (rhs); \
    deref(type) (rhs) = _t; \
}

#define mem_swap(lhs, rhs) mem_swap_t(lhs, rhs, typeof(* lhs))

#define mem_swap_gen(type) \
static inline void type##_swap(void * lhs, void * rhs) \
{ mem_swap_t(lhs, rhs, type); }

#define mem_put_gen(type) \
static inline void type##_put(void * target, const void * src) \
{ deref(type) target = deref(type) src; }

static inline void * mem_allocate(I32 size)
{
    void * ptr;

    if ((ptr = malloc(size))) return ptr;

    assert(0);
    return NULL;
}

static inline void * mem_zero(I32 size)
{
    void * ptr;

    if ((ptr = calloc(size, 1))) return ptr;

    assert(0);
    return NULL;
}

static inline void mem_del(void * ptr)
{
    free(ptr);
}

static inline void * mem_reallocate(void * ptr, I32 size)
{
    void * new_ptr;

    if ((new_ptr = realloc(ptr, size))) return new_ptr;

    assert(0);
    return NULL;
}

static inline void * mem_extend(void * ptr, I32 current_size, I32 extra_size)
{
    return mem_reallocate(ptr, current_size + extra_size);
}

static inline void mem_map(void * data, I32 n_items, I32 item_size, F f)
{
    while (n_items --)
    {
        f(data);
        data += item_size;
    }
}

static inline void mem_copy(void * restrict dst, const void * restrict src, I32 n_items, I32 item_size)
{
    memcpy(dst, src, n_items * item_size);
}

static inline void mem_move(void * dst, const void * src, I32 n_items, I32 item_size)
{
    I32 size;

    size = n_items * item_size;
    memmove(dst, src, size);
}

static inline void * mem_dup(const void * ptr, I32 size)
{
    void * new_ptr;

    new_ptr = mem_allocate(size);
    return memcpy(new_ptr, ptr, size);
}

#endif