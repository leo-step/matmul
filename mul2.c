#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1024

float A[N][N]; // float is float32 in C
float B[N][N];
float C[N][N];

int main() {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            float acc = 0;
            for (int k = 0; k < N; k++) {
                acc += A[y][k] * B[k][x];
            }
            C[y][x] = acc;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_sec = end.tv_sec - start.tv_sec;
    double elapsed_nsec = end.tv_nsec - start.tv_nsec;

    if (elapsed_nsec < 0) {
        elapsed_sec -= 1;
        elapsed_nsec += 1e9;
    }

    double total_elapsed_sec = elapsed_sec + elapsed_nsec / 1e9;
    double tflop = (double)N*N*2*N*1e-12;
    // printf("%f, %f\n", total_elapsed_sec, tflop);
    printf("%f TFLOPs\n", tflop / total_elapsed_sec);
    // 0.000572 TFLOPs

    return 0;
}