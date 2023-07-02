#ifndef BIGINT_H
#define BIGINT_H

#include "./structure/Vec.h"
#include "./type/U32.h"

typedef struct BigInt BigInt;

struct BigInt
{
    Vec digits;
};

//add mult div rem shift from str
void BigInt_inc(BigInt * lhs, const BigInt * rhs);
BigInt BigInt_add(const BigInt * lhs, const BigInt * rhs);

static inline BigInt BigInt_init(U32 n)
{
    Vec digits;

    digits = Vec_init_t(U32);
    Vec_push(& digits, n, U32);

    return (BigInt) {digits};
}

static inline I32 BigInt_n_digits(const BigInt * number)
{
    return Vec_len(& number->digits);
}

static inline void BigInt_del(BigInt * number)
{
    Vec_del(& number->digits);
}

static inline BigInt BigInt_dup(const BigInt * number)
{
    return (BigInt) {Vec_dup(& number->digits)};
}

#endif