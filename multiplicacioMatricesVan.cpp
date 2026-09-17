#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiplicacion_clasica(double *A, double *B, double *C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0.0;
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Si no pasas argumentos por consola, usará N = 1024 por defecto
    int N = (argc > 1) ? atoi(argv[1]) : 1024;

    // Reserva contigua de memoria para simulación precisa de líneas de caché
    double *A = (double *)malloc(N * N * sizeof(double));
    double *B = (double *)malloc(N * N * sizeof(double));
    double *C = (double *)malloc(N * N * sizeof(double));

    for (int i = 0; i < N * N; i++) {
        A[i] = (double)rand() / RAND_MAX;
        B[i] = (double)rand() / RAND_MAX;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    multiplicacion_clasica(A, B, C, N);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double tiempo_ms = (end.tv_sec - start.tv_sec) * 1000.0 + 
                       (end.tv_nsec - start.tv_nsec) / 1e6;

    printf("Versión Clásica | N: %d | Tiempo: %.2f ms\n", N, tiempo_ms);

    free(A); free(B); free(C);
    return 0;
}