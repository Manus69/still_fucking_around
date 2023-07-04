#ifndef DECK_H
#define DECK_H

#include "Arr.h"

#define Deck_init_t(type) Deck_init(sizeof(type))

typedef struct Deck Deck;

struct Deck
{
    Arr data;
    I32 left;
    I32 right;
};

Deck Deck_init_capacity(I32 item_size, I32 capacity);
Deck Deck_init(I32 item_size);
void * Deck_get(const Deck * deck, I32 index);

static inline I32 Deck_len(const Deck * deck)
{
    return deck->right - deck->left - 1;
}

static inline bool Deck_empty(const Deck * deck)
{
    return Deck_len(deck) == 0;
}

static inline I32 Deck_item_size(const Deck * deck)
{
    return Arr_item_size(& deck->data);
}

static inline I32 Deck_size(const Deck * deck)
{
    return Deck_len(deck) * Deck_item_size(deck);
}

static inline void Deck_del(Deck * deck)
{
    Arr_del(& deck->data);
}

static inline void * Deck_first(const Deck * deck)
{
    return Deck_get(deck, 0);
}

static inline void * Deck_last(const Deck * deck)
{
    return Deck_get(deck, Deck_len(deck) - 1);
}

static inline void Deck_set_ptr(Deck * deck, I32 index, const void * ptr, Put put)
{
    put(Deck_get(deck, index), ptr);
}

#endif