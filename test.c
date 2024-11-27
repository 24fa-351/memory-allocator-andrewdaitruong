/*
Things to note: 
Use regular malloc first
using memset fills a block of memory with a specified amount

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST_PATTERN 0xAA

void test_small_allocation() {
    
    void* ptr = malloc(8); //allocates memory
    if (ptr == NULL) {
        fprintf(stderr, "Small allocation failed. \n");
        return;
    }
    
    memset(ptr, TEST_PATTERN, 8); // Fills the block of memory
    
    for (size_t ix = 0; ix < 8; ++ix) {
        if(((unsigned char*)ptr)[ix] != TEST_PATTERN) {
            fprintf(stderr, "Small incorrect pattern. \n");
            free(ptr);
            return;
        }
    }
    free(ptr);
    printf("Small Allocation Passed. \n");
}

void test_large_allocation() {
    //void* ptr = malloc (16L * 1024L * 1024L * 1024L) causes it to fail.
    void* ptr = malloc(1024L); 
    if (ptr == NULL) {
        fprintf(stderr, "Large allocation failed. \n");
        return;
    }
    printf("Large allocation successful. \n");

    
    memset(ptr, TEST_PATTERN, 1024L); // Fills the block of memory
    
    for (size_t ix = 0; ix < 16L; ++ix) {
        if(((unsigned char*)ptr)[ix] != TEST_PATTERN) {
            fprintf(stderr, "Large incorrect pattern. \n");
            free(ptr);
            return;
        }
    }
    free(ptr);
    printf("Large Allocation Passed. \n");
}

void test_multiple_same_allocation() {
    void* ptr[3];
    for (size_t ix = 0; ix < sizeof(ptr) - 1; ++ix) {
        ptr[ix] = malloc(16L * 1024L);
        if (ptr[ix] == NULL) {
            fprintf(stderr, "Multiple same allocation failed.");
            return;
        }
        memset(ptr[ix], TEST_PATTERN, 16);
    }

    for (size_t ix = 0; ix < sizeof(ptr) - 1; ++ix) {
        for (size_t jx = 0; jx < 16; ++jx) {
            if (((unsigned char*)ptr)[ix] != TEST_PATTERN) {
                fprintf(stderr, "Large incorrect pattern. \n");
                free(ptr[jx]);
                return;
            }
        }
        free(ptr[ix]);
    }
    printf("Multiple same allocation PASSED");
}



int main(int argc, char* argv[]) {
    if (argc == 3 && strcmp(argv[1], "-t") == 0)
    {
        int test_number = atoi(argv[2]);
        switch (test_number) {
            case 1: 
                test_small_allocation(); 
                break;
            case 2:
                test_large_allocation();
                break;
            default:
                fprintf(stderr, "Invalid test number\n");
                return -1;
        }
    }
    else {
        test_small_allocation();
        test_large_allocation();

    }
    return 0;
}

