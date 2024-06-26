#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mpi.h"

int main(int argc, char* argv[]) {
    // Initiates variables
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
        then compares its own value with the previous value. If the current value is less than the previous, it sends
        a message to the master with the tag 1, indicating this process has a value that is out of order with the
        neighbour. Otherwise, it sends the message with a tag 0.
    */
    if (my_rank != 0) {
        MPI_Recv(&prev_value, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // Receive from left
        // Check if out-of-order
        if (curr_value < prev_value) {
            MPI_Send(&curr_value, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);  // Send with tag 1 if out of order
        } else {
            MPI_Send(&curr_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);  // Send with tag 0 if in order
        }
    }

    // The following sends the current value of the process to the next process
    if (my_rank != comm_sz - 1) {
        MPI_Ssend(&curr_value, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
    }

    // Master process counts the number of out-of-order processes
    if (my_rank == 0) {
        MPI_Status status;        // Status of the message
        int outOfOrderCount = 0;  // Number of processes out of order
        int recv_value;           // Value received from other processes
        for (int i = 1; i < comm_sz; i++) {  // Loop to receive messages from other processes
            // printf("\n%d\n", i);
            // Receiving messages from other processes
            MPI_Recv(&recv_value, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == 1) {  // If the tag is 1, the process is out of order
                outOfOrderCount++;      // Then increment the out of order count

                // Output the process and the value
                printf("Process %d has number %d out of order.\n", status.MPI_SOURCE, recv_value);
            }
        }
        printf("Number of processes out of order: %d\n", outOfOrderCount);  // Finally, output the final count
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}