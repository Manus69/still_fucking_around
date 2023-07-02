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

static inline BigInt _partial_mult(const BigInt * number, U32 digit, I32 place)
{
    BigInt  result;
    I32     n_digits;
    U64     product;
    U64     carry;

    result = BigInt_init(0);
    for (I32 n = 0; n < place; n ++) Vec_push(& result.digits, 0, U32);

    n_digits = BigInt_n_digits(number);
    carry = 0;

    for (I32 index = 0; index < n_digits; index ++)
    {
        product = digit * _get(number, index) + carry;
        _checked_set(& result, index + place, product % DIGIT_BASE);
        carry = product / DIGIT_BASE;
    }

    if (carry) _checked_set(& result, n_digits, carry);

    return result;
}

BigInt BigInt_mult(const BigInt * lhs, const BigInt * rhs)
{
    BigInt  result;
    BigInt  partial_result;
    I32     n_digits;

    result = BigInt_init(0);
    n_digits = BigInt_n_digits(rhs);

    for (I32 k = 0; k < n_digits; k ++)
    {
        partial_result = _partial_mult(lhs, _get(rhs, k), k);
        BigInt_inc(& result, & partial_result);

        BigInt_del(& partial_result);
    }

    return result;
}

static inline I64 _cmp(const BigInt * lhs, const BigInt * rhs)
{
    U32 lhs_digit;
    U32 rhs_digit;

    for (I32 index = BigInt_n_digits(lhs) - 1; index >= 0; index --)
    {
        lhs_digit = _get(lhs, index);
        rhs_digit = _get(rhs, index);

        if (lhs_digit != rhs_digit) return U32_cmp(& lhs_digit, & rhs_digit);
    }

    return 0;
}

I64 BigInt_cmp(const BigInt * lhs, const BigInt * rhs)
{
    I32 lhs_digits;
    I32 rhs_digits;

    lhs_digits = BigInt_n_digits(lhs);
    rhs_digits = BigInt_n_digits(rhs);

    if (lhs_digits == rhs_digits) return _cmp(lhs, rhs);

    return I32_cmp(& lhs_digits, & rhs_digits);
}