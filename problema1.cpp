#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000  // Tamaño ajustable para pruebas (ej. 1000, 2000, 5000)

double A[MAX][MAX];
double x[MAX];
double y[MAX];

void inicializar() {
    for (int i = 0; i < MAX; i++) {
        x[i] = (double)rand() / RAND_MAX;
        y[i] = 0.0;
        for (int j = 0; j < MAX; j++) {
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

int main() {
    inicializar();
    clock_t start, end;

    // --- PRIMER PAREJA DE BUCLES (Acceso por Filas / Row-Major) ---
    start = clock();
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    end = clock();
    double tiempo1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Reiniciar y
    for (int i = 0; i < MAX; i++) y[i] = 0.0;

    // --- SEGUNDA PAREJA DE BUCLES (Acceso por Columnas / Column-Major) ---
    start = clock();
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
    end = clock();
    double tiempo2 = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tiempo Par 1 (Row-Major): %f segundos\n", tiempo1);
    printf("Tiempo Par 2 (Column-Major): %f segundos\n", tiempo2);

    return 0;
}