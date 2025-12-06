#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_mangoes = 0, total_mangoes = 0;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Process ID (robot ID)
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total robots

    // Seed random number generator differently in each process
    srand(time(NULL) + rank);

    // Each robot picks between 10 to 50 mangoes
    local_mangoes = (rand() % 41) + 10;

    printf("Robot %d picked %d mangoes.\n", rank, local_mangoes);

    // Reduce all local mangoes to total_mangoes on rank 0
    MPI_Reduce(&local_mangoes, &total_mangoes, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Rank 0 prints the total
    if (rank == 0) {
        printf("\nTotal mangoes picked by %d robots: %d\n", size, total_mangoes);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}