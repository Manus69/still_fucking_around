#include "Bfd.h"

static U8 BIT_TABLE[] = 
{
    1,
    2,
    4,
    8,
    16,
    32,
    64,
    128,
};

static inline _n_bytes(I32 n_bits)
{
    return (n_bits / BPB) + 1; 
}

Bfd Bfd_init(I32 n_bits)
{
    return (Bfd) {mem_zero(_n_bytes(n_bits)), _n_bytes(n_bits)};
}

static inline I32 _byte_index(I32 bit_index)
{
    return bit_index / BPB;
}

static inline U8 _bit(I32 index)
{
    return BIT_TABLE[index % BPB];
}

bool Bfd_bit(const Bfd * bfd, I32 bit)
{
    return bfd->bytes[_byte_index(bit)] & _bit(bit);
}

void Bfd_set(Bfd * bfd, I32 bit)
{
    bfd->bytes[_byte_index(bit)] |= _bit(bit);
}

void Bfd_unset(Bfd * bfd, I32 bit)
{
    bfd->bytes[_byte_index(bit)] &= ~ _bit(bit);
}

void Bfd_toggle(Bfd * bfd, I32 bit)
{
    bfd->bytes[_byte_index(bit)] ^= _bit(bit);
}

Str Bfd_to_Str(const Bfd * bfd)
{
    Str str;
    U8  current;

    str = Str_init(bfd->n_bytes * BPB);
}