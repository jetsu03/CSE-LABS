#include <stdio.h>
#include <omp.h>

#define MAX_SIZE 100

int fib[MAX_SIZE];      // Shared array to store Fibonacci numbers
int n = 0;              // Total numbers to generate
int ready = 0;          // Synchronization flag

int main() {
    printf("Enter number of Fibonacci terms to generate: ");
    scanf("%d", &n);

    if (n > MAX_SIZE) {
        printf("Limit exceeds maximum supported size (%d).\n", MAX_SIZE);
        return 1;
    }

    // Set number of threads (2: one for generating, one for printing)
    omp_set_num_threads(2);

    #pragma omp parallel sections shared(fib, ready, n)
    {
        // Section 1: Generate Fibonacci numbers
        #pragma omp section
        {
            fib[0] = 0;
            if (n > 1) fib[1] = 1;

            for (int i = 2; i < n; i++) {
                fib[i] = fib[i - 1] + fib[i - 2];
            }

            // Signal that generation is complete
            #pragma omp flush
            ready = 1;
            #pragma omp flush(ready)
        }

        // Section 2: Print Fibonacci numbers
        #pragma omp section
        {
            // Wait until generation is complete
            while (1) {
                #pragma omp flush(ready)
                if (ready)
                    break;
            }

            // Print the series
            printf("Fibonacci Series (%d terms):\n", n);
            for (int i = 0; i < n; i++) {
                printf("%d ", fib[i]);
            }
            printf("\n");
        }
    }

    return 0;
}