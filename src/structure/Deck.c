#include "Deck.h"

#define DECK_DC (1 << 4)

static inline _left(I32 capacity)
{
    return capacity / 2;
}

static inline _right(I32 capacity)
{
    return _left(capacity) + 1;
}

Deck Deck_init_capacity(I32 item_size, I32 capacity)
{
    return (Deck) {Block_init(item_size * capacity), _left(capacity), _right(capacity)};
}

Deck Deck_init(I32 item_size)
{
    return Deck_init_capacity(item_size, DECK_DC);
}

static inline I32 _map_index(const Deck * deck, I32 index)
{
    return index + deck->left + 1;
}

void * Deck_get(const Deck * deck, I32 index)
{
    Arr_get(& deck->data, _map_index(deck, index));
}
