#ifndef U32_H
#define U32_H

#include "./core/mem.h"
#include "I64.h"
#include "to_Str.h"

mem_put_gen(U32)
mem_swap_gen(U32)
mem_cmp_gen(U32)
to_Str_gen(U32, "%u")

static inline U64 U32_hash(const void * n)
{
    return deref(U32) n;
}

#endif