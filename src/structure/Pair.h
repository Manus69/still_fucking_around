#ifndef PAIR_H
#define PAIR_H

#include "Arr.h"

#define Pair_init_t(f_type, s_type) Pair_init(sizeof(f_type), sizeof(s_type))
#define Pair_set_first(pair_ptr, val, type) \
{type _t = val; Pair_set_first_ptr(pair_ptr, & _t, type##_put);}
#define Pair_set_second(pair_ptr, val, type) \
{type _t = val; Pair_set_second_ptr(pair_ptr, & _t, type##_put);}
#define Pair_set(pair_ptr, f, s, f_type, s_type) \
    Pair_set_first(pair_ptr, f, f_type) \
    Pair_set_second(pair_ptr, s, s_type)

typedef struct Pair Pair;

struct Pair
{
    Arr data;
};

mem_put_gen(Pair)
mem_swap_gen(Pair)

static inline Pair Pair_init(I32 f_size, I32 s_size)
{
    I32 size;

    size = max(f_size, s_size);
    return (Pair) {Arr_init(size, 2)};
}

static inline void * Pair_first(const Pair * pair)
{
    return Arr_get(& pair->data, 0);
}

static inline void * Pair_second(const Pair * pair)
{
    return Arr_get(& pair->data, 1);
}

static inline void Pair_set_first_ptr(Pair * pair, const void * item, Put put)
{
    put(Pair_first(pair), item);
}

static inline void Pair_set_second_ptr(Pair * pair, const void * item, Put put)
{
    put(Pair_second(pair), item);
}

static inline void Pair_set_ptr(Pair * pair, const void * first, const void * second, Put put_f, Put put_s)
{
    Pair_set_first_ptr(pair, first, put_f);
    Pair_set_second_ptr(pair, second, put_s);
}

static inline void Pair_map_first(Pair * pair, F f)
{
    f(Pair_first(pair));
}

static inline void Pair_map_second(Pair * pair, F f)
{
    f(Pair_second(pair));
}

static inline void Pair_del(Pair * pair)
{
    Arr_del(& pair->data);
    * pair = (Pair) {0};
}

#endif