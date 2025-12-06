#include <stdio.h>
#include <omp.h>

#define NUM_SECTIONS 4

int main() {
    // Simulated item prices in each section
    double clothing[] = {49.99, 89.50, 25.00};         // 3 items
    double gaming[] = {59.99, 299.99};                 // 2 items
    double grocery[] = {3.99, 2.50, 1.25, 6.75};        // 4 items
    double stationery[] = {1.00, 2.50};                // 2 items

    // Array of pointers to sections and their sizes
    double* sections[NUM_SECTIONS] = {clothing, gaming, grocery, stationery};
    int section_sizes[NUM_SECTIONS] = {3, 2, 4, 2};

    double section_totals[NUM_SECTIONS] = {0.0};
    double final_total = 0.0;

    // Parallel processing of sections
    #pragma omp parallel for
    for (int i = 0; i < NUM_SECTIONS; i++) {
        double subtotal = 0.0;
        for (int j = 0; j < section_sizes[i]; j++) {
            subtotal += sections[i][j];
        }
        section_totals[i] = subtotal;
    }

    // Sum all section totals serially
    for (int i = 0; i < NUM_SECTIONS; i++) {
        final_total += section_totals[i];
    }
    // Output
    printf("Section-wise totals:\n");
    printf("Clothing: $%.2f\n", section_totals[0]);
    printf("Gaming: $%.2f\n", section_totals[1]);
    printf("Grocery: $%.2f\n", section_totals[2]);
    printf("Stationery: $%.2f\n", section_totals[3]);

    printf("\nFinal Bill Amount: $%.2f\n", final_total);

    return 0;
}