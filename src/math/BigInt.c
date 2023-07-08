#include "BigInt.h"
#include "../type/U32.h"
#include "./debug/debug.h"

#define BASE ((U64) 1 << (sizeof(U8) * BPB))

static inline void _reserve_back(BigInt * number, I32 capacity)
{
    Deck_reserve_back(& number->digits, capacity);
}

static inline U8 _get(const BigInt * number, I32 index)
{
    return deref(U8) Deck_get(& number->digits, index);
}

static inline U8 _checked_get(const BigInt * number, I32 index)
{
    return index < Deck_len(& number->digits) ? _get(number, index) : 0;
}

static inline void _set(BigInt * number, I32 index, U8 val)
{
    Deck_set_t(& number->digits, index, val, U8);
}

static inline void _set_push(BigInt * number, I32 index, U8 val)
{
    if (index < BigInt_n_digits(number)) return _set(number, index, val);

    Deck_push_back(& number->digits, val, U8);
}

bool BigInt_is_zero(const BigInt * number)
{
    return (BigInt_n_digits(number) == 1) && (_get(number, 0) == 0); 
}

I64 BigInt_cmp(const void * lhs, const void * rhs)
{
    I32 lhs_digits;
    I32 rhs_digits;
    I64 result;

    lhs_digits = BigInt_n_digits(lhs);
    rhs_digits = BigInt_n_digits(rhs);
    if (lhs_digits != BigInt_n_digits(rhs)) return I32_cmp(& lhs_digits, & rhs_digits);

    for (I32 index = lhs_digits - 1; index >= 0; index --)
    {
        result = U8_cmp(Deck_get(& ((BigInt *)lhs)->digits, index), 
                        Deck_get(& ((BigInt *)rhs)->digits, index));
        
        if (result) return result;
    }

    return 0;
}

static inline I32 _addition_setup(BigInt * target, const BigInt * lhs, const BigInt * rhs)
{
    I32 n_digits;
    I32 lhs_digits;
    I32 rhs_digits;

    lhs_digits = BigInt_n_digits(lhs);
    rhs_digits = BigInt_n_digits(rhs);
    n_digits = max(lhs_digits, rhs_digits);
    _reserve_back(target, n_digits + 1);

    return n_digits;
}

void BigInt_plus(BigInt * lhs, const BigInt * rhs)
{
    I32 n_digits;
    U64 result;
    U64 carry;

    carry = 0;
    n_digits = _addition_setup(lhs, lhs, rhs);
    for (I32 index = 0; index < n_digits; index ++)
    {
        result = _checked_get(lhs, index) + _checked_get(rhs, index) + carry;
        _set_push(lhs, index, result % BASE);
        carry = result / BASE;
    }

    if (carry) _set(lhs, n_digits, 1);
}

static inline void _to_zero(BigInt * number)
{
    BigInt_del(number);
    * number = BigInt_init(0);
}

void BigInt_minus(BigInt * lhs, const BigInt * rhs)
{
    I32 n_digits;
    U64 result;
    U64 carry;

    if (BigInt_cmp(lhs, rhs) <= 0) return _to_zero(lhs);

    carry = 0;
    n_digits = BigInt_n_digits(rhs);
    for (I32 index = 0; (index < n_digits) || carry; index ++)
    {
        result = _get(lhs, index) + (BASE - _checked_get(rhs, index) - carry);
        _set(lhs, index, result % BASE);
        carry = result / BASE; 
    }

    while (-- n_digits && (_get(lhs, n_digits) == 0)) Deck_pop_back(& lhs->digits);
}

BigInt BigInt_add(const BigInt * lhs, const BigInt * rhs)
{
    BigInt result;

    result = BigInt_copy(lhs);
    BigInt_plus(& result, rhs);

    return result;
}

BigInt BigInt_subt(const BigInt * lhs, const BigInt * rhs)
{
    BigInt result;

    result = BigInt_copy(lhs);
    BigInt_minus(& result, rhs);

    return result;
}

static inline void _rshift(BigInt * number, I32 n)
{
    while (n --) Deck_push_front(& number->digits, 0, U8);
}

static inline void _lshift(BigInt * number, I32 n)
{
    while (n --) Deck_pop_front(& number->digits);
}

static inline BigInt _empty()
{
    BigInt number;

    number = BigInt_init(0);
    Deck_pop_back(& number.digits);

    return number;
}

static inline BigInt _mult(const BigInt * number, U8 n)
{
    BigInt  _number;
    I32     n_digits;
    U64     result;
    U64     carry;

    _number = _empty();
    n_digits = BigInt_n_digits(number);
    carry = 0;

    for (I32 index = 0; index < n_digits; index ++)
    {
        result = _get(number, index) * n + carry;
        Deck_push_back(& _number.digits, result % BASE, U8);
        carry = result / BASE;
    }

    if (carry) Deck_push_back(& _number.digits, carry, U8);

    return _number;
}

BigInt BigInt_mult(const BigInt * lhs, const BigInt * rhs)
{
    BigInt  result;
    BigInt  partial;
    I32     n_digits;

    if (BigInt_cmp(lhs, rhs) < 0) mem_swap_t(& lhs, & rhs, Ptr);

    n_digits = BigInt_n_digits(rhs);
    result = BigInt_init(0);

    for (I32 index = 0; index < n_digits; index ++)
    {
        partial = _mult(lhs, _get(rhs, index));
        _rshift(& partial, index);
        BigInt_plus(& result, & partial);
        BigInt_del(& partial);
    }

    return result;
}

static inline U64 _compute_multiple(U8 lhs_digit, U8 rhs_digit)
{
    return ((lhs_digit * BASE) / (rhs_digit + 1));
}

static inline BigInt _get_multiple(const BigInt * lhs, const BigInt * rhs)
{
    I32     lhs_high;
    I32     rhs_high;
    I32     shift;
    U64     multiple;
    BigInt  result;

    lhs_high = BigInt_n_digits(lhs) - 1;
    rhs_high = BigInt_n_digits(rhs) - 1;

    if (lhs_high == rhs_high) return BigInt_init(_get(lhs, lhs_high) / _get(rhs, rhs_high));

    multiple = _compute_multiple(_get(lhs, lhs_high), _get(rhs, rhs_high));
    shift = multiple >= BASE ? 1 : 0;
    result = BigInt_init(shift ? multiple / BASE : multiple);
    shift += (lhs_high - rhs_high);
    _rshift(& result, shift);

    return result;
}

BigIntQR BigInt_div(const BigInt * lhs, const BigInt * rhs)
{
    BigInt remainder;
    BigInt multiple;
    BigInt partial;
    BigInt quotient;
    I64    _cmp;
    
    assert(BigInt_is_zero(rhs) == false);

    remainder = BigInt_copy(lhs);
    quotient = BigInt_init(0);

    while (true)
    {
        if ((_cmp = BigInt_cmp(& remainder, rhs)) < 0) break ;

        multiple = _get_multiple(& remainder, rhs);
        partial = BigInt_mult(& multiple, rhs);

        BigInt_minus(& remainder, & partial);
        BigInt_plus(& quotient, & multiple);

        BigInt_del(& multiple);
        BigInt_del(& partial);
    }

    return (BigIntQR) {quotient, remainder};
}