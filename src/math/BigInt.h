#ifndef BIGINT_H
#define BIGINT_H

#include "./structure/Vec.h"
#include "./type/U32.h"

typedef struct BigInt BigInt;

struct BigInt
{
    Vec digits;
};

//to do: div rem
void BigInt_inc(BigInt * lhs, const BigInt * rhs);
void BigInt_inc_U32(BigInt * lhs, U32 rhs);
I64 BigInt_cmp(const BigInt * lhs, const BigInt * rhs);
BigInt BigInt_add(const BigInt * lhs, const BigInt * rhs);
BigInt BigInt_mult(const BigInt * lhs, const BigInt * rhs);
BigInt BigInt_add_U32(const BigInt * number, U32 n);
BigInt BigInt_mult_U32(const BigInt * number, U32 n);
void BigInt_decr(BigInt * lhs, const BigInt * rhs);
void BigInt_decr_U32(BigInt * number, U32 n);
BigInt BigInt_sub(const BigInt * lhs, const BigInt * rhs);

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

static inline bool BigInt_is_zero(const BigInt * number)
{
    return (BigInt_n_digits(number) == 1) && (deref(U32) Vec_first(& number->digits) == 0); 
}

#endif