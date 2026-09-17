#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiplicacion_bloques(double *A, double *B, double *C, int N, int B_size) {
    for (int i = 0; i < N * N; i++) C[i] = 0.0;

    for (int i = 0; i < N; i += B_size) {
        for (int j = 0; j < N; j += B_size) {
            for (int k = 0; k < N; k += B_size) {
                
                for (int i1 = i; i1 < i + B_size && i1 < N; i1++) {
                    for (int j1 = j; j1 < j + B_size && j1 < N; j1++) {
                        for (int k1 = k; k1 < k + B_size && k1 < N; k1++) {
                            C[i1 * N + j1] += A[i1 * N + k1] * B[k1 * N + j1];
                        }
                    }
                }

            }
        }
    }
}

int main(int argc, char *argv[]) {

    int N = (argc > 1) ? atoi(argv[1]) : 1024;
    int B_size = (argc > 2) ? atoi(argv[2]) : 16;

    double *A = (double *)malloc(N * N * sizeof(double));
    double *B = (double *)malloc(N * N * sizeof(double));
    double *C = (double *)malloc(N * N * sizeof(double));

    for (int i = 0; i < N * N; i++) {
        A[i] = (double)rand() / RAND_MAX;
        B[i] = (double)rand() / RAND_MAX;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    multiplicacion_bloques(A, B, C, N, B_size);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double tiempo_ms = (end.tv_sec - start.tv_sec) * 1000.0 + 
                       (end.tv_nsec - start.tv_nsec) / 1e6;

    printf("Versión por Bloques | N: %d | B: %d | Tiempo: %.2f ms\n", N, B_size, tiempo_ms);

    free(A); free(B); free(C);
    return 0;
}