#include<stdio.h>
#include<mpi.h>
int main(int argc, char **argv)
  {
     char in[4];  // Send 4 characters
     int  out;    // Interprete as an integer
  
     int numprocs;
     int myid;
     int i;
  
     MPI_Init(&argc,&argv);
     MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
     MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  
     if(myid == 0)
     {
        //cout << "We have " << numprocs << " processors" << endl;
        printf("We have %d processors \n", numprocs); //Prints number of process
        // In case of rank 0 it is just receiving some information
        MPI_Recv(&out, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, NULL); 
        //Parameters
        // Buffer , Size , Data Type , Received from which processor , Tag , Comm World , Status
        //NULL used here is just a status flag
        // Process 0 on receiving the character converting it to ASCII and prints them
        //cout << "Received this number from proc 1: " << out << endl;   
        printf("Received this number from proc 1: %d", out);
     }
     else  if ( myid == 1 )
     { 
        in[0] = 'c';
  
        MPI_Send(&in, 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD); 
        // Parameter informations
        // in is the buffer which you want to send - message you want to send
        // size of the message - character so 1
        // type of the message which is MPI_CHAR - it is not the normal char
        // here we are talking abt point to point so we mention the destination which is rank
        // message tag - can be anything
        // In which world we are working
     }
  
     MPI_Finalize();
  }
