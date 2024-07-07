#include <stdlib.h>
#include "matrix.h"

void matrix_multiply(Matrix *A, Matrix *B, Matrix *C) {
    transpose_matrix(B);
    for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < B->rows; ++j) {
            for (int k = 0; k < A->cols; ++k) {
                C->data[i * C->cols + j] += A->data[i * A->cols + k] * B->data[j * B->cols + k];
                // if you assume B is transposed (like this: B->data[j * B->cols + k])
                // you get slightly higher performance because memory access better
            }
        }
    }
}