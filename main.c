#include "./debug/debug.h"
#include "./structure/Slice.h"

#include "./structure/Vec.h"
void Vec_test(I32 len)
{
    Vec v = Vec_init_t(I32);
    for (I32 k = 0; k < len; k ++)
    {
        Vec_push(& v, k, I32);
        
    }

    debug_I32(Vec_get(& v, len - 1));

    Vec_del(& v);
    printf("%zu\n", sizeof(Vec));
}

#include "./alg/sort.h"
void sort_test(I32 len)
{
    Vec v = Vec_init_t(I32);
    for (I32 k = 0; k < len; k ++)
    {
        Vec_push(& v, len - k, I32);
    }

    Slice s = Vec_to_Slice(& v);
    sort(& s, Slice, I32);
    // sort_insert(& s, I32_cmp, I32_put, I32_swap);
    // debug_Slice(& s, debug_I32);

    debug_I32(Vec_last(& v));

    Vec_del(& v);
}

#define FILE_NAME "text_file.txt"
#include "./io/io.h"
void sort_test_txt()
{
    Vec v = io_txt_file_lines(FILE_NAME);
    
    sort(& v, Vec, Str);
    debug_Vec(& v, debug_Str);

    Vec_del_items(& v, (F) Str_del);
    Vec_del(& v);
}

#include "./structure/Set.h"
void Set_test()
{
    Set s = Set_init_t(I32);
    I32 N = 1 << 5;

    for (I32 k = 0; k < N; k ++)
    {
        Set_insert(& s, & k, I32);
    }

    debug_Set(& s, debug_I32);

    Set_del(& s);
}

#include "./math/BigInt.h"
void BigInt_test()
{
    BigInt a = BigInt_from_cstr("999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999");
    // debug_BigInt(& a);
    BigInt b = BigInt_from_cstr("999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999"
    "999999999""999999999""999999999""999999999""999999999");

    BigInt c = BigInt_mult(& a, & b);

    debug_BigInt2(& c);
    // debug_BigInt(& c);

    BigInt_del(& a);
    BigInt_del(& b);
    BigInt_del(& c);
}

#include "./structure/Deck.h"
void Deck_test(I32 len)
{
    Deck d = Deck_init_t(I32);
    for (I32 k = 0; k < len; k ++)
    {
        Deck_push_back(& d, len - k, I32);
    }

    for (I32 k = 0; k < len; k ++)
    {
        Deck_push_front(& d, len - k, I32);
    }

    debug_Deck(& d, debug_I32);
    Deck_del(& d);
}

//bitfield heap pair
int main()
{
    // sort_test(1 << 25);
    // sort_test_txt();
    // Set_test();
    BigInt_test();
    // Deck_test(10);

}