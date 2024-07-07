#include <stdbool.h>

#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    float* data;
} Matrix;

Matrix *new_matrix(int N, int M);

Matrix *random_matrix(int N, int M, int seed);

void free_matrix(Matrix *matrix);

void save_matrix(Matrix *matrix, const char* filename);

void load_matrix(Matrix *matrix, const char* filename);

bool equal(Matrix *A, Matrix *B);

void matrix_multiply(Matrix *A, Matrix *B, Matrix *C);

void matrix_multiply_baseline(Matrix *A, Matrix *B, Matrix *C);

void transpose_matrix(Matrix *A);

void print_matrix(Matrix *matrix);

#endif