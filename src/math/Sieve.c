#include "Sieve.h"

static inline void _cast_out(Bfd * bfd, I32 len, I32 index, U64 step)
{
    U64 n_steps;

    n_steps = (len - index) / step;
    index += step;

    while (n_steps --)
    {
        Bfd_unset(bfd, index);
        index += step;
    }
}

static inline I32 _next_index(const Bfd * bfd, I32 index, I32 len)
{
    while (index < len)
    {
        if (Bfd_bit(bfd, index)) return index;
        index ++;
    }

    return NO_INDEX;
}

#define SIEVE_MINC (1 << 5)
Sieve Sieve_init(I32 n)
{
    Bfd bits;
    I32 index;

    n = n < SIEVE_MINC ? SIEVE_MINC : n;
    bits = Bfd_init_ones(n);
    Bfd_unset(& bits, 0);
    Bfd_unset(& bits, 1);
    index = 2;

    while (index != NO_INDEX)
    {
        _cast_out(& bits, n, index, index);
        index = _next_index(& bits, index + 1, n);
    }

    return (Sieve) {bits, n};
}