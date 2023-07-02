#include "BigInt.h"
#include "../type/U32.h"
#include "./debug/debug.h"

#define DIGIT_BASE (((U64) 1) << 32)

static inline U32 _get(const BigInt * number, I32 index)
{
    return deref(U32) Vec_get(& number->digits, index);
}

static inline U32 _checked_get(const BigInt * number, I32 index)
{
    return index < BigInt_n_digits(number) ? _get(number, index) : 0;
}

static inline void _set(BigInt * number, I32 index, U32 digit)
{
    Vec_set_ptr(& number->digits, index, & digit, U32_put);
}

static inline void _checked_set(BigInt * number, I32 index, U32 digit)
{
    if (index >= BigInt_n_digits(number)) return Vec_push_ptr(& number->digits, & digit, U32_put);

    return _set(number, index, digit);
}

static inline void _reserve(BigInt * number, I32 capacity)
{
    Vec_reserve(& number->digits, capacity);
}

static inline I32 _max_digits(const BigInt * lhs, const BigInt * rhs)
{
    I32 lhs_digits;
    I32 rhs_digits;

    lhs_digits = BigInt_n_digits(lhs);
    rhs_digits = BigInt_n_digits(rhs);

    return max(lhs_digits, rhs_digits);
}

void BigInt_inc(BigInt * lhs, const BigInt * rhs)
{
    I32 n_digits;
    I32 index;
    U64 result;
    U64 carry;

    n_digits = _max_digits(lhs, rhs);
    index = 0;
    carry = 0;

    while (index < n_digits)
    {
        result = _checked_get(lhs, index) + _checked_get(rhs, index) + carry;
        _checked_set(lhs, index, result % DIGIT_BASE);
        carry = result / DIGIT_BASE;
        index ++;
    }

    if (carry) _checked_set(lhs, index, 1);
}

BigInt BigInt_add(const BigInt * lhs, const BigInt * rhs)
{
    BigInt result;

    result = BigInt_dup(lhs);
    BigInt_inc(& result, rhs);

    return result;
}

static inline Vec _digit_shift(Vec * digits, I32 n)
{
    
}

void BigInt_shift(BigInt * number, I32 n)
{
    ;

}

BigInt BigInt_mult(const BigInt * lhs, const BigInt * rhs)
{

}