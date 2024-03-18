#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    // Get number of processes and check only 3 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 3)
    {
        printf("This application is meant to be run with 3 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    // Determine root's process rank
    int root_rank = 0;
 
    switch(my_rank)
    {
        case 0:
        {
            // Define my value
            int my_value = 100;
 
            // Define the receive counts
            int counts[3] = {1, 1, 3}; // Here we need to mention number of elements will be receivved from each process separately in a form of array
 
            // Define the displacements
            int displacements[3] = {0, 3, 5}; // This is stride or displacement more kind of starting index where we want the elements received from the process to be stored
 
            int* buffer = (int*)calloc(8, sizeof(int)); // Here we are mentioning the memory space needed to be allocated so here we need to mention total number of elements that we will be receiving from all the process
            printf("Process %d, my value = %d.\n", my_rank, my_value);
            MPI_Gatherv(&my_value, 1, MPI_INT, buffer, counts, displacements, MPI_INT, root_rank, MPI_COMM_WORLD); // Buffer is the array where the elements will be received
            printf("Values gathered in the buffer on process %d:", my_rank);
            for(int i = 0; i < 8; i++)
            {
                printf(" %d", buffer[i]);
            }
            printf("\n");
            free(buffer);
            break;
        }
        case 1:
        {
            // Define my value
            int my_value = 101;
 
            printf("Process %d, my value = %d.\n", my_rank, my_value);
            MPI_Gatherv(&my_value, 1, MPI_INT, NULL, NULL, NULL, MPI_INT, root_rank, MPI_COMM_WORLD);
            break;
        }
        case 2:
        {
            // Define my values
            int my_values[3] = {102, 103, 104}; //Here we need to create a array of elements to be shared
 
            printf("Process %d, my values = %d %d %d.\n", my_rank, my_values[0], my_values[1], my_values[3]); // Here also while printing make sure you are printing all the elements you are sending
            MPI_Gatherv(my_values, 3, MPI_INT, NULL, NULL, NULL, MPI_INT, root_rank, MPI_COMM_WORLD); //Second parameter is number of elements sent by this particular process
            break;
        }
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}