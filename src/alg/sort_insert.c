#include "sort.h"

void sort_insert(Slice * slice, Cmp cmp, Put put, Swap swap)
{
    I32     length;
    I32     sorted;
    void *  lhs;
    void *  rhs;

    (void) put;
    length = Slice_len(slice);
    
    for (I32 index = 1; index < length; index ++)
    {
        sorted = index - 1;
        while (sorted >= 0)
        {
            lhs = Slice_get(slice, sorted);
            rhs = Slice_get(slice, sorted + 1);

            if (cmp(lhs, rhs) > 0) swap(lhs, rhs);
            else break ;
            
            sorted --;
        }
    }
}