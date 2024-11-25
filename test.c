#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_manager.h"

// Simple test for the custom malloc, free, and realloc
void test_malloc_free_realloc() {
    printf("Running malloc, free, realloc test...\n");

    // Test malloc
    void* ptr1 = malloc_custom(100);
    if (ptr1 == NULL) {
        printf("Malloc failed!\n");
    } else {
        printf("Malloc succeeded for 100 bytes\n");
    }

    // Test realloc (increase size)
    void* ptr2 = realloc_custom(ptr1, 200);
    if (ptr2 == NULL) {
        printf("Realloc failed!\n");
    } else {
        printf("Realloc succeeded for 200 bytes\n");
    }

    // Test free
    free_custom(ptr2);
    printf("Free succeeded\n");
}

int main(int argc, char* argv[]) {
    test_malloc_free_realloc();
    return 0;
}
