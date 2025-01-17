#include <stdlib.h>
#include <arm_neon.h>
#include "matrix.h"

#define TILE_SIZE 4 // required for SIMD

void tile_multiply(Matrix *A, Matrix *B, Matrix *C, int ii, int jj) {
    float32x4_t vA_l[TILE_SIZE];
    float32x4_t vB_l[TILE_SIZE];

    for (int i = ii; i < ii + TILE_SIZE; i++) {
        vA_l[i-ii] = vld1q_f32(&(A->data[i * A->cols]));
    } 

    for (int j = jj; j < jj + TILE_SIZE; j++) {
        vB_l[j-jj] = vld1q_f32(&(B->data[j * B->cols]));
    } 

    for (int i = ii; i < ii + TILE_SIZE; i++) {
        for (int j = jj; j < jj + TILE_SIZE; j++) {
            float32x4_t vC = vld1q_f32(&(C->data[i * C->cols + j]));
            float32x4_t vr = vfmaq_f32(vC, vA_l[i-ii], vB_l[j-jj]);
            vst1q_f32(&(C->data[i * C->cols + j]), vr);
        }
    }
}

void matrix_multiply(Matrix *A, Matrix *B, Matrix *C) {
    transpose_matrix(B);
    for (int ii = 0; ii < A->rows; ii += TILE_SIZE) {
        for (int jj = 0; jj < B->cols; jj += TILE_SIZE) {
            tile_multiply(A, B, C, ii, jj);
        }
    }
}