#ifndef U8_H
#define U8_H

#include "../core/mem.h"

mem_swap_gen(U8);
mem_put_gen(U8);
mem_cmp_gen(U8)

static inline U64 U8_hash(const void * x)
{
    return deref(U8) x;
}

#endif