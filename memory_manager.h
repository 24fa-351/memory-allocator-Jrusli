#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>

#define ALIGN_SIZE 8  // Alignment for memory blocks

// Memory block structure
typedef struct Block {
    size_t size;  // Size of the block (including metadata)
    struct Block* next;  // Pointer to the next block in the free list
} Block;

// Function declarations
void* malloc_custom(size_t size);
void free_custom(void* ptr);
void* realloc_custom(void* ptr, size_t size);
void* get_me_blocks(ssize_t how_much);

#endif // MEMORY_MANAGER_H
