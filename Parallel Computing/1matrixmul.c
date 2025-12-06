#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter size of matrix/vector (n): ");
    scanf("%d", &n);

    // Dynamically allocate memory
    double **A = (double **)malloc(n * sizeof(double *));
    double *x = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    // Initialize matrix A and vector x
    printf("Enter elements of matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("Enter elements of vector x (%d elements):\n", n);
    for (int i = 0; i < n; i++)
        scanf("%lf", &x[i]);

    // Matrix-vector multiplication: y = A * x
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        y[i] = 0.0;
        for (int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    // Output result
    printf("Result vector y = A * x:\n");
    for (int i = 0; i < n; i++)
        printf("%lf\n", y[i]);

    // Free memory
    for (int i = 0; i < n; i++)
        free(A[i]);
    free(A);
    free(x);
    free(y);

    return 0;
}