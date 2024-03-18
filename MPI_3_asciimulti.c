#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv) {
    char in[4];  // Send 4 characters
    char out1, out2, out3, out4;    // Receive as characters

    int numprocs;
    int myid;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if(myid == 0) {
        printf("We have %d processors \n", numprocs);

        MPI_Recv(&out1, 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD, NULL);
        printf("Received this character from proc 1: %c, ASCII value: %d\n", out1, (int)out1);

        MPI_Recv(&out2, 1, MPI_CHAR, 2, 0, MPI_COMM_WORLD, NULL);
        printf("Received this character from proc 2: %c, ASCII value: %d\n", out2, (int)out2);

        MPI_Recv(&out3, 1, MPI_CHAR, 3, 0, MPI_COMM_WORLD, NULL);
        printf("Received this character from proc 3: %c, ASCII value: %d\n", out3, (int)out3);



    } else if (myid == 1) {
        in[0] = 'a';
        MPI_Send(&in, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else if (myid == 2) {
        in[0] = 'b';
        MPI_Send(&in, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else if (myid == 3) {
        in[0] = 'c';
        MPI_Send(&in, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
