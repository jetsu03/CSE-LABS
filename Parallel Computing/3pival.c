#include <stdio.h>
#include <omp.h>

int main() {
    long num_steps = 100000000; // More steps = more accurate
    double step = 1.0 / (double)num_steps;
    double sum = 0.0;

    double start_time = omp_get_wtime();

    // Parallel region with reduction
    #pragma omp parallel
    {
        double x;
        double local_sum = 0.0;

        #pragma omp for
        for (long i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            local_sum += 1.0 / (1.0 + x * x);
        }

        #pragma omp atomic
        sum += local_sum;
    }

    double pi = 4.0 * step * sum;

    double end_time = omp_get_wtime();

    printf("Computed value of Pi = %.15f\n", pi);
    printf("Execution Time = %f seconds\n", end_time - start_time);

    return 0;
}