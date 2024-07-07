#include <stdlib.h>
#include "matrix.h"

void matrix_multiply(Matrix *A, Matrix *B, Matrix *C) {
    for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < B->cols; ++j) {
            for (int k = 0; k < A->cols; ++k) {
                C->data[i * C->cols + j] += A->data[i * A->cols + k] * B->data[k * B->cols + j];
            }
        }
    }
}