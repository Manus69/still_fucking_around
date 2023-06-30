#ifndef SORT_H
#define SORT_H

#include "../structure/Slice.h"

#define sort_slice(slice_ptr, type) sort_merge(slice_ptr, type##_cmp, type##_put, type##_swap)
#define sort(ptr, container_type, item_type) \
{Slice _s = container_type##_to_Slice(ptr); sort_slice(& _s, item_type);}

void sort_merge(Slice * slice, Cmp cmp, Put put, Swap swap);
void sort_heap(Slice * slice, Cmp cmp, Put put, Swap swap);

#endif