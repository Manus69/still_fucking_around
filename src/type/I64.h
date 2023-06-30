#ifndef I64_H
#define I64_H

#include "../core/mem.h"

mem_put_gen(I64)
mem_swap_gen(I64)

static inline I64 I64_cmp(const void * lhs, const void * rhs)
{
    return deref(I64) lhs - deref(I64) rhs;
}

static inline U64 I64_hash(const void * n)
{
    return deref(I64) n;
}

#endif