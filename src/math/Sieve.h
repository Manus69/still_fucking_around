#ifndef SIEVE_H
#define SIEVE_H

#include "./structure/Bfd.h"
#include "./structure/Vec.h"

#define SIEVE_DEFAULT_FILE_NAME "./src/math/__primes"

typedef struct Sieve Sieve;

struct Sieve
{
    Bfd data;
    U64 length;
};

Sieve   Sieve_init(U32 n);
Sieve   Sieve_from_file(I32 n);
STATUS  Sieve_to_file(U32 n);
Vec     Sieve_primes_less(const Sieve * sieve, U32 n);

static inline U64 Sieve_len(const Sieve * sieve)
{
    return sieve->length;
}

static inline bool Sieve_is_prime(const Sieve * sieve, U64 n)
{
    return Bfd_bit(& sieve->data, n);
}

static inline void Sieve_del(Sieve * sieve)
{
    Bfd_del(& sieve->data);
    * sieve = (Sieve) {0};
}

#endif