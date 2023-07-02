#ifndef BLOCK_H
#define BLOCK_H

#include "../core/mem.h"

typedef struct Block Block;

struct Block
{
    void *  bytes;
    I32     size;
};

static inline Block Block_init(I32 size)
{
    return (Block) {mem_allocate(size), size};
}

static inline Block Block_init_zero(I32 size)
{
    return (Block) {mem_zero(size), size};
}

static inline Block Block_dup(const Block * block)
{
    return (Block) {mem_dup(block->bytes, block->size), block->size};
}

static inline void Block_del(Block * block)
{
    mem_del(block->bytes);
    * block = (Block) {0};
}

static inline I32 Block_size(const Block * block)
{
    return block->size;
}

static inline void * Block_get(const Block * block, I32 offset)
{
    return block->bytes + offset;
}

static inline void Block_extend(Block * block, I32 extra_size)
{
    block->bytes = mem_extend(block->bytes, block->size, extra_size);
    block->size += extra_size;
}

static inline void Block_extend_zero(Block * block, I32 extra_size)
{
    block->bytes = mem_extend_zero(block->bytes, block->size, extra_size);
    block->size += extra_size;
}

#endif