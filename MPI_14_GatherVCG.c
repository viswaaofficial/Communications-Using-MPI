#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int buffer[6];
    int rank, size, i;
    int receive_counts[4] = { 0, 1, 2, 3 };
    int receive_displacements[4] = { 0, 0, 1, 3 };

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Here for rank=0 its not even storing anything , for rank 1 it is store 1 element which is 1 and 
    //for rank 2 its having 2 elements (2,2) and similarly 3 for rank 3 (3,3,3)

    for (i=0; i<rank; i++)
    {
        buffer[i] = rank;
    }

    // Here gather v is called at once for all i.e both root and non root together so lets see in detail
    // for root i.e 0 the number of send is 0 so nothing is send
    // for roor 1 then numofsend is 1 so 1 elements is send 
    // similarly for root 2 and 3 its 2 and 3 respectively
    // Total we have 6
    // Here the buffer for send is again used for recieve -- need to be taken care here, even if we have diff buffers 

    MPI_Gatherv(buffer, rank, MPI_INT, buffer, receive_counts, receive_displacements, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for (i=0; i<6; i++)
        {
            printf("[%d]", buffer[i]);
        }
        printf("\n");
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}