#include "Deck.h"

#define DECK_DC (1 << 4)

static inline I32 _left(I32 capacity)
{
    return capacity / 2;
}

static inline I32 _right(I32 capacity)
{
    return _left(capacity) + 1;
}

Deck Deck_init_capacity(I32 item_size, I32 capacity)
{
    return (Deck) {Arr_init(item_size, capacity), _left(capacity), _right(capacity)};
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
    return Arr_get(& deck->data, _map_index(deck, index));
}

static inline I32 _back_capacity(const Deck * deck)
{
    return Arr_len(& deck->data) - deck->right;
}

static inline I32 _front_capacity(const Deck * deck)
{
    return deck->left;
}

static inline void _extend_back(Deck * deck, I32 n_items)
{
    Arr_extend(& deck->data, n_items);
}

static inline void _extend_front(Deck * deck, I32 n_items)
{
    Arr_extend(& deck->data, n_items);
    mem_move(Deck_get(deck, n_items), Deck_get(deck, 0), n_items, Deck_item_size(deck));
    deck->left += n_items;
    deck->right += n_items;
}

static inline bool _no_front_capacity(const Deck * deck)
{
    return _front_capacity(deck) == 0;
}

static inline bool _no_back_capacity(const Deck * deck)
{
    return _back_capacity(deck) == 0;
}

void Deck_push_back_ptr(Deck * deck, const void * item, Put put)
{
    if (unlikely(_no_back_capacity(deck))) _extend_back(deck, Deck_len(deck));

    Arr_set_ptr(& deck->data, deck->right ++, item, put);
}

void Deck_push_front_ptr(Deck * deck, const void * item, Put put)
{
    if (unlikely(_no_front_capacity(deck))) _extend_front(deck, Deck_len(deck));

    Arr_set_ptr(& deck->data, deck->left --, item, put);
}

void Deck_reserve_back(Deck * deck, I32 n_items)
{
    if (_back_capacity(deck) >= n_items) return ;

    _extend_back(deck, n_items - _back_capacity(deck));
}

void Deck_reserve_front(Deck * deck, I32 n_items)
{
    if (_front_capacity(deck) >= n_items) return ;

    _extend_front(deck, n_items - _front_capacity(deck));
}

//сафнов алекс