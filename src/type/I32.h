#ifndef I32_H
#define I32_H

#include "../core/mem.h"

mem_swap_gen(I32);
mem_put_gen(I32);

static inline I64 I32_cmp(const void * lhs, const void * rhs)
{
    return deref(I32) lhs - deref(I32) rhs;
}

static inline U64 I32_hash(const void * n)
{
    return deref(I32) n;
}

#endif