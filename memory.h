#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

#define ALIGN_SIZE 8  


typedef struct Block {
    size_t size;  
    struct Block* next; 
} Block;

// Function declarations
void* malloc_custom(size_t size);
void free_custom(void* ptr);
void* realloc_custom(void* ptr, size_t size);
void* get_me_blocks(size_t block_size);

#endif // MEMORY_H
