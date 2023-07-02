#ifndef U64_H
#define U64_H

#include "./core/mem.h"

mem_swap_gen(U64)
mem_put_gen(U64)

static inline I64 U64_cmp(const void * lhs, const void * rhs)
{
    return deref(U64) lhs < deref(U64) rhs ? -1 : deref(U64) lhs > deref(U64) rhs; 
}

static inline U64 U64_hash(const void * n)
{
    return deref(U64) n;
}

#endif