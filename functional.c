#include "functional.h"

//#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include <math.h>

// Convert boolean spikes to float
// TODO: leave for now, do in each function separately
void *convert_array(void *x);

// 1D array compare
// Allocate result before, so we don't have to do malloc() in function
//void compare_array_1d(void const *x, void const *y, bool *result, size_t const size, char const *op)
//{
//    // Check whether arrays are of same type (sort of)
//    // Checking size of arrays is not possible, given that they're pointers
//    assert(sizeof(x[0]) == sizeof(y[0]));
//
//    // Go over array
//    for (int i = 0; i < size; i++)
//    {
//        // Different types of comparisons
//        // First do operators that consist of two characters,
//        // since "<=" could also be seen as "<" when only comparing the first char
//        if (strncmp(op, "<=", 2) == 0)
//        {
//            result[i] = (x[i] <= y[i]);
//        }
//        else if (strncmp(op, ">=", 2) == 0)
//        {
//            result[i] = (x[i] >= y[i]);
//        }
//        else if (strncmp(op, "!=", 2) == 0)
//        {
//            result[i] = (x[i] >= y[i]);
//        }
//        else if (strncmp(op, "==", 2) == 0)
//        {
//            result[i] = (x[i] >= y[i]);
//        }
//        else if (strncmp(op, "<", 1) == 0)
//        {
//            result[i] = ((float) x[i] < (float) y[i]);
//        }
//        else if (strncmp(op, ">", 1) == 0)
//        {
//            result[i] = (x[i] > y[i]);
//        }
//        else
//        {
//            printf("Invalid operator: %s", op);
//            return NULL;
//        }
//    }
//}


// View (connection-type fold)
void *view_array(void *x, int const *shape);

// Sum dimension (neuron-type fold)
void *sum_dimension(void *x, int const dim);

// Copy array (for weights)
void *copy_array(void const *x);

// Print 1D array
void print_array_1d(void const *x, size_t const size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", x[i]);
    }
    printf("\n");
}
