#include <stdlib.h>
#include "matrix.h"

#define TILE_SIZE 8 // best size was 8

void tile_multiply(Matrix *A, Matrix *B, Matrix *C, int ii, int jj, int kk) {
    for (int i = ii; i < ii + TILE_SIZE; i++) { // loop order?
        for (int j = jj; j < jj + TILE_SIZE; j++) {
            for (int k = kk; k < kk + TILE_SIZE; k++) {
                C->data[i * C->cols + j] += A->data[i * A->cols + k] * B->data[k * B->cols + j];
                // if you assume B is transposed (like this: B->data[j * B->cols + k])
                // you get slightly higher performance because memory access better
            }
        }
    }
}

void matrix_multiply(Matrix *A, Matrix *B, Matrix *C) {
    for (int ii = 0; ii < A->rows; ii += TILE_SIZE) {
        for (int jj = 0; jj < B->cols; jj += TILE_SIZE) {
            for (int kk = 0; kk < A->cols; kk += TILE_SIZE) {
                tile_multiply(A, B, C, ii, jj, kk);
            }
        }
    }
}