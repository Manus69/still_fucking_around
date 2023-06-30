#include "Vec.h"
#include <stdbool.h>

static inline bool _no_capacity(const Vec * vec)
{
    return Vec_remaining_capacity(vec) == 0;
}

static inline void _double_capacity(Vec * vec)
{
    Arr_extend(& vec->arr, vec->index);
}

void Vec_push_ptr(Vec * vec, const void * item, Put put)
{
    if (unlikely(_no_capacity(vec))) _double_capacity(vec);

    Vec_set_ptr(vec, vec->index ++, item, put);
}