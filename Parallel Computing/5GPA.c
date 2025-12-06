#include <stdio.h>
#include <omp.h>

#define MAX_STUDENTS 100

int main() {
    int n;
    double cgpas[MAX_STUDENTS];
    int max_index = 0;
    double max_cgpa = 0.0;

    // Input number of students
    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n > MAX_STUDENTS || n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    // Input CGPAs
    printf("Enter CGPAs of %d students:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Student %d: ", i + 1);
        scanf("%lf", &cgpas[i]);
    }

    // Parallel search for highest CGPA
    #pragma omp parallel
    {
        double local_max = 0.0;
        int local_index = 0;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            if (cgpas[i] > local_max) {
                local_max = cgpas[i];
                local_index = i;
            }
        }

        #pragma omp critical
        {
            if (local_max > max_cgpa) {
                max_cgpa = local_max;
                max_index = local_index;
            }
        }
    }

    // Output the result
    printf("\nStudent with the highest CGPA:\n");
    printf("Student %d with CGPA = %.2f\n", max_index + 1, max_cgpa);

    return 0;
}