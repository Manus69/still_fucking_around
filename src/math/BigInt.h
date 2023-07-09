#ifndef BIGINT_H
#define BIGINT_H

#include "./structure/Deck.h"
#include "./type/type.h"

typedef struct BigInt BigInt;

struct BigInt
{
    Deck digits;
};

typedef struct BigIntQR BigIntQR;

struct BigIntQR
{
    BigInt quotient;
    BigInt remainder;
};

mem_swap_gen(BigInt)
mem_put_gen(BigInt)

bool BigInt_is_zero(const BigInt * number);
I64 BigInt_cmp(const void * lhs, const void * rhs);
void BigInt_plus(BigInt * lhs, const BigInt * rhs);
void BigInt_minus(BigInt * lhs, const BigInt * rhs);
BigInt BigInt_add(const BigInt * lhs, const BigInt * rhs);
BigInt BigInt_subt(const BigInt * lhs, const BigInt * rhs);
BigInt BigInt_mult(const BigInt * lhs, const BigInt * rhs);
BigIntQR BigInt_div(const BigInt * lhs, const BigInt * rhs);
Str BigInt_to_Str(const BigInt * number);
BigInt BigInt_from_Str(const Str * str);
BigInt BigInt_from_cstr(const char * cstr);

//
//U8 is a placeholder, change to U32
//
static inline BigInt BigInt_init(U8 n)
{
    Deck digits;

    digits = Deck_init_t(n);
    Deck_push_back(& digits, n, U8);

    return (BigInt) {digits};
}

static inline I32 BigInt_n_digits(const BigInt * number)
{
    return Deck_len(& number->digits);
}

static inline void BigInt_del(BigInt * number)
{
    Deck_del(& number->digits);
}

static inline BigInt BigInt_copy(const BigInt * number)
{
    return (BigInt) {Deck_copy(& number->digits)};
}

static inline BigInt * BigIntQR_quotient(const BigIntQR * qr)
{
    return (BigInt *) & (qr->quotient);
}

static inline BigInt * BigIntQR_remainder(const BigIntQR * qr)
{
    return (BigInt *) & (qr->remainder);
}

static inline void BigIntQR_del(BigIntQR * qr)
{
    BigInt_del(& qr->quotient);
    BigInt_del(& qr->remainder);
}

#endif