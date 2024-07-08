#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "matrix.h"

#define N 4096

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

int main() {
    Matrix *A = random_matrix(N, N, 0);
    Matrix *B = random_matrix(N, N, 1);
    Matrix *C = new_matrix(N, N);
    Matrix *C_true = new_matrix(N, N);
    
    char filename[100];
    snprintf(filename, sizeof(filename), "C_true_%d", N);

    if (file_exists(filename)) {
        load_matrix(C_true, filename);
    } else {
        matrix_multiply_baseline(A, B, C_true);
        save_matrix(C_true, filename);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    matrix_multiply(A, B, C);

    clock_gettime(CLOCK_MONOTONIC, &end);

    // puts("======= Matrix A =======");
    // print_matrix(A);
    // puts("======= Matrix B =======");
    // print_matrix(B);
    // puts("======= Matrix C =======");
    // print_matrix(C);
    // puts("======= Matrix C_true =======");
    // print_matrix(C_true);

    assert(equal(C, C_true));

    double elapsed_sec = end.tv_sec - start.tv_sec;
    double elapsed_nsec = end.tv_nsec - start.tv_nsec;

    if (elapsed_nsec < 0) {
        elapsed_sec -= 1;
        elapsed_nsec += 1e9;
    }

    double total_elapsed_sec = elapsed_sec + elapsed_nsec / 1e9;
    double gflop = (double)N*N*2*N*1e-9;
    printf("%f GFLOPs\n", gflop / total_elapsed_sec);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(C_true);

    return 0;
}