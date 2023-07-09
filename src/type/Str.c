#include "Str.h"
#include "../structure/Vec.h"

Str Str_concat(const Str * lhs, const Str * rhs)
{
    Str new_str;
    I32 length;

    length = Str_len(lhs) + Str_len(rhs);
    new_str = Str_init(length);
    memcpy(new_str.bytes, lhs->bytes, Str_len(lhs));
    memcpy(new_str.bytes + Str_len(lhs), rhs->bytes, Str_len(rhs) + 1);

    return new_str;
}

static inline void _extend(Str * str, I32 n_bytes)
{
    str->bytes = mem_extend(str->bytes, str->capacity, n_bytes);
    str->capacity += n_bytes;
}

static inline void _check_extend(Str * str, I32 n_bytes)
{
    n_bytes = n_bytes > Str_len(str) ? n_bytes : Str_len(str);
    _extend(str, n_bytes);
}

static inline STATUS _check_capacity(const Str * str, I32 n_bytes)
{
    return str->capacity - str->length > n_bytes ? STATUS_OK : STATUS_NOT_OK;
}

static inline void _check(Str * str, I32 n_bytes)
{
    if (unlikely(_check_capacity(str, n_bytes) == STATUS_NOT_OK)) _check_extend(str, n_bytes);
}

void Str_append(Str * lhs, const Str * rhs)
{
    _check(lhs, Str_len(rhs));

    memcpy(Str_last(lhs) + 1, rhs->bytes, Str_len(rhs) + 1);
    lhs->length += Str_len(rhs);
}

void Str_append_c(Str * str, char c)
{
    _check(str, 1);

    deref(char) (Str_last(str) + 1) = c;
    str->length ++;
    deref(char) (Str_last(str) + 1) = '\0';
}

static inline I32 _find_c(const Slice * slice, char c)
{
    I32     length;
    char *  bytes;

    bytes = Slice_first(slice);
    length = Slice_len(slice);

    for (I32 k = 0; k < length; k ++)
    {
        if (bytes[k] == c) return k;
    }

    return NO_INDEX;
}

Slice Str_split_next_c(Slice * str_slice, char c)
{
    I32 index;

    index = _find_c(str_slice, c);

    if (index == NO_INDEX) return Slice_chop_all(str_slice);

    return Slice_chop(str_slice, index + 1);
}

Vec Str_split_c(const Str * str, char c)
{
    Vec     strings;
    Slice   slice;
    Slice   current;

    strings = Vec_init_t(Str);
    slice = Str_to_Slice(str);

    while (Slice_empty(& slice) == false)
    {
        current = Str_split_next_c(& slice, c);
        Vec_push(& strings, Str_from_Slice(& current), Str);
    }

    return strings;
}