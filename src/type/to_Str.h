#ifndef TO_STR_H
#define TO_STR_H

#include "Str.h"
#include <stdio.h>

#define to_Str_gen(type, format) \
static inline Str type##_to_Str(const void * ptr) \
{ \
    char buffer[sizeof(type) * BPB] = {0}; \
    snprintf(buffer, sizeof(type) * BPB, format, deref(type) ptr); \
    return Str_from_cstr(buffer); \
}

#endif 