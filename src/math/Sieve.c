#include "Sieve.h"
#include "./io/io.h"

static inline void _cast_out(Bfd * bfd, U64 len, I64 index, I64 step)
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

static inline I64 _next_index(const Bfd * bfd, I64 index, I64 len)
{
    while (index < len)
    {
        if (Bfd_bit(bfd, index)) return index;
        index ++;
    }

    return NO_INDEX;
}

#define SIEVE_MINC (1 << 5)
Sieve Sieve_init(U32 n)
{
    Bfd bits;
    I64 index;

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

STATUS Sieve_to_file(U32 n)
{
    Sieve   sieve;
    STATUS  status;

    sieve = Sieve_init(n);
    status = io_write_to_file(  SIEVE_DEFAULT_FILE_NAME, 
                                Bfd_as_bytes(& sieve.data), 
                                Bfd_size(& sieve.data));
    Sieve_del(& sieve);

    return status;
}

Sieve Sieve_from_file(I32 n)
{
    Str bytes;
    Bfd bfd;

    bytes = io_file_read(SIEVE_DEFAULT_FILE_NAME);
    bfd = Bfd_init_from_bytes(Str_first(& bytes), (n / BPB) + 1);

    return (Sieve) {bfd, n};
}

Vec Sieve_primes_less(const Sieve * sieve, U32 n)
{
    Vec primes;
    U64 len;

    primes = Vec_init_t(U64);
    len = Sieve_len(sieve);
    len = n > len ? len : n;

    for (U64 index = 0; index < len; index ++)
    {
        if (Sieve_is_prime(sieve, index)) Vec_push(& primes, index, U64);
    }

    return primes;
}