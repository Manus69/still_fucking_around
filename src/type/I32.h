#ifndef I32_H
#define I32_H

#include "../core/mem.h"
#include "to_Str.h"

mem_swap_gen(I32)
mem_put_gen(I32)
mem_cmp_gen(I32)
to_Str_gen(I32, "%ld")

static inline U64 I32_hash(const void * n)
{
    return deref(I32) n;
}

#endif