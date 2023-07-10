#ifndef SIEVE_H
#define SIEVE_H

#include "./structure/Bfd.h"

typedef struct Sieve Sieve;

struct Sieve
{
    Bfd data;
    I32 length;
};

Sieve Sieve_init(I32 n);

static inline I32 Sieve_len(const Sieve * sieve)
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