#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mpi.h"

int main(int argc, char* argv[]) {
    // Init variables
    int comm_sz;     // Number of processes
    int my_rank;     // My process rank
    int curr_value;  // Current process's unique value
    int prev_value;  // Previous process's unique value

    MPI_Init(NULL, NULL);                     // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);  // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);  // Get the rank of the process

    // Generate a random integer number to assign to each rank
    srand(time(NULL) + my_rank);  // Seed the random generator
    curr_value = rand() % 100;
    // printf("Rank %d: %d\n", my_rank, curr_value);

    /*
        The following is for processes other than the master. These processes will receive a previous process's value,
        then compares its own value with the previous value. If the current value is less than the previous, prints the
        process and the value that is out of order.
    */
    if (my_rank != 0) {
        // Receive the previous value from the left neighbour
        MPI_Recv(&prev_value, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Check if out-of-order
        if (curr_value < prev_value) {
            printf("Process %d has number %d out of order.\n", my_rank, curr_value);  // Print the process and the value
        }
    }

    // If rank is not the last, send the current value to the next rank
    if (my_rank != comm_sz - 1) {
        // Send the current value to the next rank
        MPI_Send(&curr_value, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
    }

    printf("Process %d has finished.\n", my_rank);  // Print the process has finished

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}