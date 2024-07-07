#include "matrix.h"

Matrix *matrix_multiply(Matrix *A, Matrix *B, Matrix *C) {
    int a_rows = A->rows;
    int a_cols = A->cols;
    int b_cols = B->cols;
    int c_cols = C->cols;

    for (int i = 0; i < a_rows; ++i) {
        for (int j = 0; j < b_cols; ++j) {
            C->data[i * c_cols + j] = 0;
            for (int k = 0; k < a_cols; ++k) {
                C->data[i * c_cols + j] += A->data[i * a_cols + k] * B->data[k * b_cols + j];
            }
        }
    }

    return C;
}