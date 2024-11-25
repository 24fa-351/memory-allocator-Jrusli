#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "memory_manager.h"

static Block* free_list = NULL;  // Head of the free list (simple array implementation)

void* get_me_blocks(ssize_t how_much) {
    void* ptr = sbrk(0);  // Get current program break
    if (sbrk(how_much) == (void*)-1) {  // Request more memory from the OS
        return NULL;
    }
    return ptr;
}

void* malloc_custom(size_t size) {
    if (size == 0) {
        return NULL;
    }

    size_t aligned_size = (size + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1);  // Align to 8-byte boundary
    Block* block = free_list;
    Block* prev = NULL;

    // Search the free list for a suitable block
    while (block != NULL) {
        if (block->size >= aligned_size) {
            // Remove block from free list
            if (prev != NULL) {
                prev->next = block->next;
            } else {
                free_list = block->next;
            }
            return (void*)(block + 1);  // Return memory just after the block's metadata
        }
        prev = block;
        block = block->next;
    }

    // No suitable block found, acquire more memory
    block = (Block*)get_me_blocks(aligned_size + sizeof(Block));
    if (!block) {
        return NULL;  // Memory allocation failed
    }

    block->size = aligned_size;  // Set size
    return (void*)(block + 1);  // Return memory just after the block's metadata
}

void free_custom(void* ptr) {
    if (!ptr) {
        return;
    }

    Block* block = (Block*)ptr - 1;  // Get block metadata
    block->next = free_list;  // Add block to the free list
    free_list = block;
}

void* realloc_custom(void* ptr, size_t size) {
    if (!ptr) {
        return malloc_custom(size);  // If pointer is NULL, behave like malloc
    }

    if (size == 0) {
        free_custom(ptr);  // If size is 0, behave like free
        return NULL;
    }

    Block* block = (Block*)ptr - 1;
    size_t aligned_size = (size + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1);

    if (aligned_size <= block->size) {
        return ptr;  // If the new size is smaller or equal, return the same block
    }

    // Allocate a new block and copy the contents
    void* new_ptr = malloc_custom(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size);  // Copy the old data to the new block
        free_custom(ptr);  // Free the old block
    }
    return new_ptr;
}
