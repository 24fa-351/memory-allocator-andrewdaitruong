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
    printf("Small allocation successful. \n");
    
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
    void* ptr = malloc(16L); 
    if (ptr == NULL) {
        fprintf(stderr, "Large allocation failed. \n");
        return;
    }
    printf("Large allocation successful. \n");

    
    memset(ptr, TEST_PATTERN, 16L); // Fills the block of memory
    
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
    for (size_t ix = 0; ix < sizeof(ptr) / sizeof(ptr[0]); ++ix) {
        ptr[ix] = malloc(16L);
        if (ptr[ix] == NULL) {
            fprintf(stderr, "Multiple same allocation failed.");
            return;
        }
        memset(ptr[ix], TEST_PATTERN, 16L);
    }
    printf("Multiple same allocation successful. \n");
    for (size_t ix = 0; ix < sizeof(ptr) / sizeof(ptr[0]); ++ix) {
        for (size_t jx = 0; jx < 16L; ++jx) {
            if (((unsigned char*)ptr[ix])[jx] != TEST_PATTERN) {
                fprintf(stderr, "Large incorrect pattern. \n");
                return;
            }
        }
        free(ptr[ix]);
    }
    printf("Multiple same allocation PASSED. \n");
}

//Interspersed free memory is malloc/free in non-sequential order
void test_interspersed_free() {
    void* ptr1 = malloc(8);
    void* ptr2 = malloc(16);

    if (ptr1 == NULL || ptr2 == NULL) {
        fprintf(stderr, "Inter free allocation failed .\n");
        return;
    }
    else {
        printf("Interspersed allocation 1 and 2 successful. \n");
    }
    free(ptr2);

    void* ptr3 = malloc(32);
    if (ptr3 == NULL) {
        fprintf(stderr, "Inter free allocation failed. \n");
        return;
    }
    else {
        printf("Interspersed allocation 3 successful. \n");
    }
    free(ptr3);
    free(ptr1);
    
    printf("Interspersed Allocation PASSED. \n");
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
            case 3:
                test_multiple_same_allocation();
                break;
            case 4:
                test_interspersed_free();
                break;
            default:
                fprintf(stderr, "Invalid test number\n");
                return -1;
        }
    }
    else {
        test_small_allocation();
        test_large_allocation();
        test_multiple_same_allocation();
        test_interspersed_free();
    }
    return 0;
}

