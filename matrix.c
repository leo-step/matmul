#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

Matrix *new_matrix(int N, int M) {
    float *data = (float *)calloc(N*M, sizeof(float));
    if (data == NULL) {
        free(data);
        return NULL;
    }
    
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (matrix == NULL) {
        free(matrix);
        return NULL;
    }
    matrix->rows = N;
    matrix->cols = M;
    matrix->data = data;

    return matrix;
}

Matrix *random_matrix(int N, int M, int seed) {
    srand(seed);

    Matrix *matrix = new_matrix(N, M);
    float *data = matrix->data;

    for (int i = 0; i < N*M; i++) {
        data[i] = (float)rand() / (float)RAND_MAX;
    }

    matrix->data = data;

    return matrix;
}

void free_matrix(Matrix *matrix) {
    free(matrix->data);
    free(matrix);
}

void save_matrix(Matrix *matrix, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    fwrite(&matrix->rows, sizeof(matrix->rows), 1, file);
    fwrite(&matrix->cols, sizeof(matrix->cols), 1, file);

    fwrite(matrix->data, sizeof(float), matrix->rows * matrix->cols, file);

    fclose(file);
}

void load_matrix(Matrix *matrix, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }

    fread(&matrix->rows, sizeof(matrix->rows), 1, file);
    fread(&matrix->cols, sizeof(matrix->cols), 1, file);

    matrix->data = (float*)malloc(matrix->rows * matrix->cols * sizeof(float));
    if (!matrix->data) {
        perror("Failed to allocate memory for matrix data");
        fclose(file);
        return;
    }

    fread(matrix->data, sizeof(float), matrix->rows * matrix->cols, file);

    fclose(file);
}

bool equal(Matrix *A, Matrix *B) {
    if (A->rows != B->rows || A->cols != B->cols) {
        return false;
    }

    for (int i = 0; i < A->rows * A->cols; i++) {
        if (A->data[i] - B->data[i] > 1e7) {
            return false;
        }
    }

    return true;
}

void matrix_multiply_baseline(Matrix *A, Matrix *B, Matrix *C) {
    for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < B->cols; ++j) {
            C->data[i * C->cols + j] = 0;
            for (int k = 0; k < A->cols; ++k) {
                C->data[i * C->cols + j] += A->data[i * A->cols + k] * B->data[k * B->cols + j];
            }
        }
    }
}

void transpose_matrix(Matrix *A) {
    float* transposed_data = (float*)malloc(A->rows * A->cols * sizeof(float));
    if (transposed_data == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->cols; ++j) {
            transposed_data[j * A->rows + i] = A->data[i * A->cols + j];
        }
    }

    free(A->data);

    A->data = transposed_data;
    int temp = A->rows;
    A->rows = A->cols;
    A->cols = temp;
}

void print_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            printf("%f ", matrix->data[i * matrix->cols + j]);
        }
        printf("\n");
    }
}