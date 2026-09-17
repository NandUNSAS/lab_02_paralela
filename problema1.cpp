#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void benchmark_bucles(int N, double *t_row, double *t_col) {
    // Asignación dinámica de memoria
    double **A = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
    }
    double *x = (double *)malloc(N * sizeof(double));
    double *y = (double *)malloc(N * sizeof(double));

    if (A == NULL || x == NULL || y == NULL) {
        printf("Error: No se pudo asignar memoria para N = %d\n", N);
        return;
    }

    // Inicialización
    for (int i = 0; i < N; i++) {
        x[i] = (double)rand() / RAND_MAX;
        y[i] = 0.0;
        for (int j = 0; j < N; j++) {
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }

    struct timespec start, end;

    // --- PRIMERA PAREJA DE BUCLES (Row-Major) ---
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    *t_row = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1e6;

    // Reiniciar y
    for (int i = 0; i < N; i++) y[i] = 0.0;

    // --- SEGUNDA PAREJA DE BUCLES (Column-Major) ---
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    *t_col = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1e6;

    // Liberación de recursos
    for (int i = 0; i < N; i++) free(A[i]);
    free(A); free(x); free(y);
}

int main() {
    // Escala segura dentro del límite de memoria RAM común
    int tamanos[] = {1000, 5000, 10000, 20000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    printf("%-10s | %-20s | %-20s\n", "Tamano (N)", "Row-Major (ms)", "Column-Major (ms)");
    printf("-----------------------------------------------------------\n");

    for (int k = 0; k < num_tamanos; k++) {
        double t_row = 0, t_col = 0;
        benchmark_bucles(tamanos[k], &t_row, &t_col);
        printf("%-10d | %-20.2f | %-20.2f\n", tamanos[k], t_row, t_col);
    }

    return 0;
}