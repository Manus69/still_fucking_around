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



static inline void Bfd_del(Bfd * bfd)
{
    mem_del(bfd->bytes);
    * bfd = (Bfd) {0};
}

#endif