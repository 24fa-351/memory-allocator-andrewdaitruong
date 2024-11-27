#include "memory.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct Mem_Block {
    size_t size;
    struct Block* next;
    int free;
} Mem_Block;

#define BLOCK_SIZE sizeof(Mem_Block)

static Mem_Block* list = NULL; // free blocks

void* get_me_blocks(size_t amount) {
    return sbrk(amount);
}

void* custom_malloc(size_t size) {
    if (size <= 0) {
        fprintf(stderr, "Size cannot be under 1\n");
        return NULL;
    }
    
    Mem_Block* block = list;
    while (block) {
        if (block->free && block->size >= size) {
            fprintf(stderr, "block size cannot be bigger than regular size\n");
            block->free =0;
            return; //
        }
        block = block->next;
    }

    // Allocates new block
    block == sbrk(size + BLOCK_SIZE);
    if (block == NULL) {
        return;
    }

    block->size = size;
    block->next = NULL;
    block->free = 0;

    return (void*)(block + 1); // Returns usable memory
}

void* custom_free(void* ptr) {
    if (!ptr) {
        return;
    }
    Mem_Block* block = (Mem_Block*)ptr - 1;
    block->free = 1; // Marks block as free
}

void* custom_realloc(void* ptr, size_t new_size) {
    if (!ptr) {
        return custom_malloc(new_size);
    }
    if (new_size == 0) {
        custom_free(ptr);
        fprintf(stderr, "You cannot free a block of 0\n");
        return NULL;
    }

    Mem_Block* block = (Mem_Block*)ptr - 1;

    //Remember to account for size and errors with size
    if (block->size >= new_size) {
        return ptr;
    }

    // Remember to check for NULLS
    void* next_ptr = custom_malloc(new_size);
    if (!next_ptr) {
        fprintf(stderr, "Cannot be NULL\n");
        return NULL;
    }

    memcpy(next_ptr, ptr, block->size);
    custom_free(ptr);
    return next_ptr;
}