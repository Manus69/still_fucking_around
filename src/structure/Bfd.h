#ifndef BFD_H
#define BFD_H

#include "Vec.h"
#include "./type/type.h"

typedef struct Bfd Bfd;

struct Bfd
{
    U8 * bytes;
    I32  n_bytes;
};

Bfd     Bfd_init(I32 n_bits);
Bfd     Bfd_init_ones(I32 n_bits);
Bfd     Bfd_init_from_bytes(const void * bytes, I32 n_bytes);
bool    Bfd_bit(const Bfd * bfd, I32 bit);
void    Bfd_set(Bfd * bfd, I32 bit);
void    Bfd_unset(Bfd * bfd, I32 bit);
void    Bfd_toggle(Bfd * bfd, I32 bit);
Str     Bfd_to_Str(const Bfd * bfd);

static inline void Bfd_del(Bfd * bfd)
{
    mem_del(bfd->bytes);
    * bfd = (Bfd) {0};
}

static inline U8 * Bfd_as_bytes(const Bfd * bfd)
{
    return bfd->bytes;
}

static inline I32 Bfd_size(const Bfd * bfd)
{
    return bfd->n_bytes;
}

#endif