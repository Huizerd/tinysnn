#include "functional.h"

#include <stdio.h>

// Test functional functions
int main() {
    // Arrays for comparison: int, float
    int a[10] = {0};
    int b[10] = {1};
    float c[10] = {1.0};
    float d[10] = {2.0};

    // Array to store result
    bool result[10] = {false};

    // Pointer before compare
    printf("Pointer: %p\n", (void *) &result);

    // Compare
    // If we want to allow multiple types (just converting everything to float)
    // and then compare, can we still use size_t? I guess we'd need int because sizeof()
    // wouldn't work?
//    compare_array_1d(a, b, result, sizeof(a) / sizeof(a[0]), "<");
    print_array_1d(a, sizeof(a) / sizeof(a[0]));
    print_array_1d(result, sizeof(result) / sizeof(result[0]));

    // Pointer after compare
    printf("Pointer: %p\n", (void *) &result);
    return 0;
}