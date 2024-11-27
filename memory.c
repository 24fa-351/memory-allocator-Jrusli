#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "memory.h"

static Block* free_lt = NULL; 

void* get_me_blocks(size_t block_size) {
    void* ptr = sbrk(0); 
    if (sbrk(block_size) == (void*)-1) {  
        return NULL;
    }
    return ptr;
}

void* malloc_custom(size_t size) {
    if (size == 0) {
         fprintf(stderr, "Error\n");
        return NULL;
    }

    size_t aligned_size = (size + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1); 
    Block* block = free_lt;
    Block* prev = NULL;

   
    while (block != NULL) {
        if (block->size >= aligned_size) {
           
            if (prev != NULL) {
                prev->next = block->next;
            } else {
                free_lt = block->next;
            }
            return (void*)(block + 1);  
        }
        prev = block;
        block = block->next;
    }


    block = (Block*)get_me_blocks(aligned_size + sizeof(Block));
    if (!block) {
        return NULL;  
    }

    block->size = aligned_size;  
    return (void*)(block + 1); 
}

void free_custom(void* ptr) {
    if (!ptr) {
        return;
    }

    Block* block = (Block*)ptr - 1;
    block->next = free_lt; 
    free_lt = block;
}

void* realloc_custom(void* ptr, size_t size) {
    if (!ptr) {
        return malloc_custom(size); 
    }

    if (size == 0) {
        free_custom(ptr);                                    
        return NULL;
    }

    Block* block = (Block*)ptr - 1;
    size_t aligned_size = (size + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1);

    if (aligned_size <= block->size) {
        return ptr;  
    }


    void* ptr_new = malloc_custom(size);
    if (ptr_new) {
        memcpy(ptr_new, ptr, block->size);  
        free_custom(ptr);  
    }
    return ptr_new;
}
