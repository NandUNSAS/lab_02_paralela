#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Multiplicación clásica de matrices C = A * B (3 bucles anidados)
void multiplicacion_clasica(double **A, double **B, double **C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Tamaños variados para observar diferencias significativas en desempeño
    int tamanos[] = {128, 256, 512, 1024, 2048};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    printf("%-12s | %-20s\n", "Tamaño (N)", "Tiempo de Ejecución (ms)");
    printf("-----------------------------------------\n");

    for (int t = 0; t < num_tamanos; t++) {
        int N = tamanos[t];

        // Reserva dinámica de memoria
        double **A = (double **)malloc(N * sizeof(double *));
        double **B = (double **)malloc(N * sizeof(double *));
        double **C = (double **)malloc(N * sizeof(double *));
        for (int i = 0; i < N; i++) {
            A[i] = (double *)malloc(N * sizeof(double));
            B[i] = (double *)malloc(N * sizeof(double));
            C[i] = (double *)malloc(N * sizeof(double));
        }

        // Inicialización de matrices con datos aleatorios
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = (double)rand() / RAND_MAX;
                B[i][j] = (double)rand() / RAND_MAX;
            }
        }

        // Medición de tiempo de ejecución
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        multiplicacion_clasica(A, B, C, N);

        clock_gettime(CLOCK_MONOTONIC, &end);
        double tiempo_ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                           (end.tv_nsec - start.tv_nsec) / 1e6;

        printf("%-12d | %-20.2f\n", N, tiempo_ms);

        // Liberación de memoria
        for (int i = 0; i < N; i++) {
            free(A[i]); free(B[i]); free(C[i]);
        }
        free(A); free(B); free(C);
    }

    return 0;
}