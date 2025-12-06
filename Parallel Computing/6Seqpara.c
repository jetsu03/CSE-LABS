#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Function to allocate and initialize matrices
void initialize_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand() % 10;  // Small random numbers
}

// Function to allocate a square matrix
double **allocate_matrix(int n) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
        matrix[i] = (double *)malloc(n * sizeof(double));
    return matrix;
}

// Function to free a square matrix
void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

// Sequential matrix multiplication
void multiply_sequential(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Parallel matrix multiplication
void multiply_parallel(double **A, double **B, double **C, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {
    int n;
    printf("Enter matrix size (e.g. 1000, 2000, 3000): ");
    scanf("%d", &n);

    // Seed RNG
    srand(time(NULL));

    // Allocate matrices
    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);
    double **C_seq = allocate_matrix(n);
    double **C_par = allocate_matrix(n);

    // Initialize input matrices
    initialize_matrix(A, n);
    initialize_matrix(B, n);

    // Sequential multiplication
    double start_seq = omp_get_wtime();
    multiply_sequential(A, B, C_seq, n);
    double end_seq = omp_get_wtime();

    // Parallel multiplication
    double start_par = omp_get_wtime();
    multiply_parallel(A, B, C_par, n);
    double end_par = omp_get_wtime();

    // Compare results (optional, for correctness)
    int correct = 1;
    for (int i = 0; i < n && correct; i++)
        for (int j = 0; j < n; j++)
            if (C_seq[i][j] != C_par[i][j]) {
                correct = 0;
                break;
            }

    printf("\nMatrix size: %dx%d\n", n, n);
    printf("Sequential Time: %.4f seconds\n", end_seq - start_seq);
    printf("Parallel Time:   %.4f seconds\n", end_par - start_par);
    printf("Speedup:         %.2fx\n", (end_seq - start_seq) / (end_par - start_par));
    printf("Result match:    %s\n", correct ? "YES" : "NO");

    // Cleanup
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C_seq, n);
    free_matrix(C_par, n);

    return 0;
}