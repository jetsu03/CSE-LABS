#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int msg;

    MPI_Init(&argc, &argv);                 // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get current process ID
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    if (size < 4) {
        if (rank == 0) {
            printf("Please run with at least 4 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Blocking Send/Recv between process 0 and 1
    if (rank == 0) {
        msg = 100;
        printf("Process 0 (blocking) sending message: %d to Process 1\n", msg);
        MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);  // Blocking send
    }
    else if (rank == 1) {
        MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Blocking recv
        printf("Process 1 (blocking) received message: %d from Process 0\n", msg);
    }

    // Non-blocking Send/Recv between process 2 and 3
    if (rank == 2) {
        msg = 200;
        MPI_Request request;
        printf("Process 2 (non-blocking) initiating send of message: %d to Process 3\n", msg);
        MPI_Isend(&msg, 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &request); // Non-blocking send
        MPI_Wait(&request, MPI_STATUS_IGNORE);  // Wait for send to complete
    }
    else if (rank == 3) {
        MPI_Request request;
        printf("Process 3 (non-blocking) initiating receive from Process 2\n");
        MPI_Irecv(&msg, 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &request); // Non-blocking recv
        MPI_Wait(&request, MPI_STATUS_IGNORE);  // Wait for receive to complete
        printf("Process 3 (non-blocking) received message: %d from Process 2\n", msg);
    }

    MPI_Finalize(); // Finalize MPI
    return 0;
}