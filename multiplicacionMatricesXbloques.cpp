#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Multiplicación por Bloques con 6 bucles anidados
void multiplicacion_bloques(double **A, double **B, double **C, int N, int B_size) {
    // Inicializar C en 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
        }
    }

    // 6 bucles anidados: 3 externos para bloques, 3 internos para los elementos
    for (int i = 0; i < N; i += B_size) {
        for (int j = 0; j < N; j += B_size) {
            for (int k = 0; k < N; k += B_size) {
                
                // Bucles internos dentro de cada bloque
                for (int i1 = i; i1 < i + B_size && i1 < N; i1++) {
                    for (int j1 = j; j1 < j + B_size && j1 < N; j1++) {
                        for (int k1 = k; k1 < k + B_size && k1 < N; k1++) {
                            C[i1][j1] += A[i1][k1] * B[k1][j1];
                        }
                    }
                }

            }
        }
    }
}

int main() {
    int tamanos[] = {128, 256, 512, 1024, 2048};
    int bloques[] = {16, 32, 64, 128};
    
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    int num_bloques = sizeof(bloques) / sizeof(bloques[0]);

    printf("%-10s | %-12s | %-20s\n", "Matriz (N)", "Bloque (B)", "Tiempo de Ejecución (ms)");
    printf("---------------------------------------------------\n");

    for (int t = 0; t < num_tamanos; t++) {
        int N = tamanos[t];

        // Reserva dinámica
        double **A = (double **)malloc(N * sizeof(double *));
        double **B = (double **)malloc(N * sizeof(double *));
        double **C = (double **)malloc(N * sizeof(double *));
        for (int i = 0; i < N; i++) {
            A[i] = (double *)malloc(N * sizeof(double));
            B[i] = (double *)malloc(N * sizeof(double));
            C[i] = (double *)malloc(N * sizeof(double));
        }

        // Inicialización
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = (double)rand() / RAND_MAX;
                B[i][j] = (double)rand() / RAND_MAX;
            }
        }

        // Probar distintos tamaños de bloque
        for (int b = 0; b < num_bloques; b++) {
            int B_size = bloques[b];

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            multiplicacion_bloques(A, B, C, N, B_size);

            clock_gettime(CLOCK_MONOTONIC, &end);
            double tiempo_ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                               (end.tv_nsec - start.tv_nsec) / 1e6;

            printf("%-10d | %-12d | %-20.2f\n", N, B_size, tiempo_ms);
        }

        // Liberación
        for (int i = 0; i < N; i++) {
            free(A[i]); free(B[i]); free(C[i]);
        }
        free(A); free(B); free(C);
        printf("---------------------------------------------------\n");
    }

    return 0;
}