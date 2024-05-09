/*  File: arraysum.c
 *  Shang-Ian Tan, a1818695 - 2024.05.09
 *  Assignment 2, Part 2 - OpenMP
 *
 *
 *  Purpose:    Familiarization with OpenMP through a simple program that uses an array of size 1000.
 *              The program comprises two loops, one to initialise an array, the other to sum the numbers in the array.
 *              The program will print two results, the sum computed sequentially, and then as computed in parallel,
 *              using OpenMP pragmas.
 *
 *  Compile:    gcc -g -Wall -fopenmp -o arraysum arraysum.c
 *  Run:        ./arraysum <number of threads>
 *
 *  Input:      None required other that initial number of threads called with the program.
 *  Output:     The sum of the array elements computed sequentially and in parallel with OpenMP.
 *
 *  Steps:
 *  1. Initialise the array such that the ith element contains i.
 *  2. Write a sequential for loop to sum the elements of the array, and print the sequential sum.
 *  3. Write a parallel for loop to initialise the array.
 *  4. Parallelize the summation loop using a parallel directive to establish a team of threads to carry out
 *     the summation, and then a reduction clause to compute the global sum. Print the parallel computed sum.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Check if OpenMP is supported by the compiler
#ifdef _OPENMP
#include <omp.h>
#endif

#define N 1000

int main(int argc, char* argv[]) {
    int sequentialSum = 0, parallelSum = 0;  // Declare variables to store the sums of the array
    int arr[N];                              // Declare an array of size N

    // Step 1: Initialising array such that arr[i] = i
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }

    // Step 2: Sequential summation
    for (int i = 0; i < N; i++) {
        sequentialSum += arr[i];
    }
    printf("Sequential sum: %d\n", sequentialSum);

// ===================================================================================================
//
// ===================================================================================================
// Step 3: Parallel Loop to initialise array
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }

    // Step 4: Parallel summation with the parallel directive, as well as a
    // reduction clause to compute global sum into a variable parallelSum
#pragma omp parallel reduction(+ : parallelSum)
    {
        int localSum = 0;                        // Declare a local variable to store the sum of each thread
        int threadID = omp_get_thread_num();     // Get the thread ID
        int numThreads = omp_get_num_threads();  // Get the total number of threads
        int chunkSize = N / numThreads;          // Calculate the chunk size for each thread

        int startIndex = threadID * chunkSize;  // Calculate the starting index for the current thread
        int endIndex = startIndex + chunkSize;  // Calculate the ending index for the current thread

        // Handle the case where N is not divisible by the number of threads
        if (threadID == numThreads - 1) {
            endIndex = N;
        }

        // Perform the summation for the current thread
        for (int i = startIndex; i < endIndex; i++) {
            localSum += arr[i];
        }

// Accumulate the local sums into the global sum
#pragma omp critical
        {
            parallelSum += localSum;
        }
    }
    printf("Parallel sum: %d\n", parallelSum);

    return 0;
}
