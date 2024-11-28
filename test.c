#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"


void test_malloc_free_realloc() {
    printf("Running malloc, free test\n");


    void* ptr1 = malloc_custom(100);
    if (ptr1 == NULL) {
        printf("Malloc failed!\n");
        return;
    } else {
        printf("Malloc successful for 100 bytes\n");
    }

   
    void* ptr2 = realloc_custom(ptr1, 200);
    if (ptr2 == NULL) {
        printf("Realloc failed!\n");
        return;
    } else {
        printf("Realloc successful for 200 bytes\n");
    }

  
    free_custom(ptr2);
    printf("Free successful\n");
}

int main(int argc, char* argv[]) {
    test_malloc_free_realloc();
    printf("everything passed! \n");
    return 0;
}
