#ifndef BFD_H
#define BFD_H

#include "Vec.h"
#include "./type/type.h"

typedef struct Bfd Bfd;

struct Bfd
{
    Arr bytes;
};

static inline Bfd Bfd_init(I32 n_bits)
{

}

static inline bool Bfd_bit(const Bfd * bfd, I32 index)
{

}

void Bfd_set(Bfd * bfd, I32 bit)
{

}

void Bfd_toggle(Bfd * bfd, I32 bit)
{

}

Str Bfd_to_Str(const Bfd * bfd)
{

}

static inline void Bfd_del(Bfd * bfd)
{
    Arr_del(& bfd->bytes);
    * bfd = (Bfd) {0};
}

#endif