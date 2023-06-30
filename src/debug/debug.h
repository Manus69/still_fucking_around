#ifndef DEBUG_H
#define DEBUG_H

#include "./core/mem.h"
#include "./type/type.h"
#include "./structure/Arr.h"
#include "./structure/Slice.h"
#include "./structure/Vec.h"

#include <stdio.h>

#define _debug(ptr, type, format) printf(format, deref(type) ptr)

static inline void debug_nl()
{
    printf("\n");
}

static inline void debug_char(const void * ptr)
{
    _debug(ptr, char, "%c ");
}

static inline void debug_I32(const void * ptr)
{
    _debug(ptr, I32, "%ld ");
}

static inline void debug_I64(const void * ptr)
{
    _debug(ptr, I64, "%ld ");
}

static inline void debug_U32(const void * ptr)
{
    _debug(ptr, U32, "%lu ");
}

static inline void debug_U8(const void * ptr)
{
    _debug(ptr, U8, "%u ");
}

static inline void debug_cstr(const void * cstr)
{
    _debug(cstr, char *, "%s ");
}

#define debug_mem(ptr, n_items, f, type) mem_apply(ptr, n_items, sizeof(type), f)

static inline void debug_Slice(const void * slice, void (* f)(const void *))
{
    Slice_map((Slice *)slice, (F) f);
    debug_nl();
}

static inline void debug_Arr(const void * arr, void (* f)(const void *))
{
    Slice slice;

    slice = Arr_to_Slice(arr);
    debug_Slice(& slice, f);
}

static inline void debug_Vec(const void * vec, void (* f)(const void *))
{
    Slice slice;

    slice = Vec_to_Slice(vec);
    debug_Slice(& slice, f);
}

static inline void debug_Str(const void * str)
{
    char * cstr;

    cstr = Str_to_cstr(str);
    debug_cstr(& cstr);
}

// static inline void debug_BitField(const void * field)
// {
//     Str str;

//     str = BitField_to_Str(field);
//     debug_Str(& str);
//     debug_nl();

//     Str_destroy_structure(& str);
// }

// static inline void debug_Set(const void * set, void (* f)(const void *))
// {
//     Set_map((Set *) set, (F) f);
//     debug_nl();
// }

// static inline void debug_Heap(const void * heap, void (* f)(const void *))
// {
//     Heap_map((Heap *) heap, (F) f);
//     debug_nl();
// }

// static inline void debug_BigInt(const void * bigint)
// {
//     Str str;

//     str = BigInt_to_Str(bigint);
//     debug_Str(& str);
//     debug_nl();

//     Str_destroy_structure(& str);
// }

#endif