#ifndef I64_H
#define I64_H

#include "../core/mem.h"

mem_put_gen(I64)
mem_swap_gen(I64)
mem_cmp_gen(I64)

static inline U64 I64_hash(const void * n)
{
    return deref(I64) n;
}

#endif