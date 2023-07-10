#ifndef STR_H
#define STR_H

#include "../core/mem.h"
#include "../structure/Slice.h"
#include "../structure/Vec.h"

typedef struct Str Str;

struct Str
{
    char *  bytes;
    I32     length;
    I32     capacity;
};

mem_put_gen(Str)
mem_swap_gen(Str)
mem_swap_gen(char)

Str     Str_concat(const Str * lhs, const Str * rhs);
void    Str_append(Str * lhs, const Str * rhs);
void    Str_append_c(Str * str, char c);
Slice   Str_split_next_c(Slice * str_slice, char c);
Vec     Str_split_c(const Str * str, char c);

static inline I32 Str_cmp(const void * lhs, const void * rhs)
{
    return strcmp(((Str *)lhs)->bytes, ((Str *)rhs)->bytes);
}

static inline Str Str_init(I32 capacity)
{
    return (Str) {(char *) mem_zero(capacity + 1), 0, capacity + 1};
}

static inline Str Str_from_cstr(const char * cstr)
{
    I32 length;

    length = strlen(cstr);

    return (Str) {strdup(cstr), length, length + 1};
}

static inline Str Str_own(const char * cstr, I32 length)
{
    return (Str) {(char *) cstr, length, length + 1};
}

static inline Str Str_from_ptr(const void * ptr, I32 length)
{
    Str str;

    str = Str_init(length);
    memcpy(str.bytes, ptr, length);

    return str;
}

static inline void Str_del(Str * str)
{
    mem_del(str->bytes);
}

static inline I32 Str_len(const Str * str)
{
    return str->length;
}

static inline U64 Str_hash_djb2(const Str * str)
{
    U64     hash;
    char *  current;
    I32     length;
    
    hash = 5381;
    current = str->bytes;
    length = Str_len(str);

    while (length --)
        hash = ((hash << 5) + hash) + (U64)(* current ++);

    return hash;
}

static inline U64 Str_hash(const Str * str)
{
    return Str_hash_djb2(str);
}

static inline Str Str_from_Slice(const Slice * slice)
{
    return Str_from_ptr(Slice_ptr(slice), Slice_len(slice));
}

static inline Slice Str_to_Slice(const Str * str)
{
    return Slice_init(str->bytes, sizeof(char), Str_len(str));
}

static inline char * Str_to_cstr(const Str * str)
{
    return str->bytes;
}

static inline char Str_at(const Str * str, I32 index)
{
    return str->bytes[index];
}

static inline char * Str_get(const Str * str, I32 index)
{
    return & str->bytes[index];
}

static inline char * Str_first(const Str * str)
{
    return Str_get(str, 0);
}

static inline char * Str_last(const Str * str)
{
    return Str_get(str, Str_len(str) - 1);
}

static inline void Str_set(Str * str, I32 index, char c)
{
    str->bytes[index] = c;
}

static inline I32 Str_find_c(const Str * str, char c)
{
    I32 length;

    length = Str_len(str);
    for (I32 k = 0; k < length; k ++)
    {
        if (Str_at(str, k) == c) return k;
    }

    return NO_INDEX;
}

static inline void Str_rev(Str * str)
{
    Slice slice;

    slice = Str_to_Slice(str);
    Slice_rev(& slice, char_swap);
}



#endif