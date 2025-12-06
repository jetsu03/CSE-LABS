#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size, i;
    int n = 4; // total elements
    int data[4] = {1, 2, 3, 4};
    int recv;
    int squared;
    int gathered[4];
    int total_sum;

    MPI_Init(&argc, &argv); // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process ID
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes

    if (size != n) {
        if (rank == 0) {
            printf("Run with exactly %d processes.\n", n);
        }
        MPI_Finalize();
        return 0;
    }

    // Broadcast n to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter the array to all processes
    MPI_Scatter(data, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process squares its received value
    squared = recv * recv;

    // Gather the squared results to root process
    MPI_Gather(&squared, 1, MPI_INT, gathered, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Reduce to calculate sum of squares
    MPI_Reduce(&squared, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print results at root
    if (rank == 0) {
        printf("Squared values: ");
        for (i = 0; i < n; i++) {
            printf("%d ", gathered[i]);
        }
        printf("\nSum of squares = %d\n", total_sum);
    }

    MPI_Finalize(); // Finalize MPI
    return 0;
}