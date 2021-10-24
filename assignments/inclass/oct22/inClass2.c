#include <stdio.h>
#include <mpi.h>

#define SIZE 640000

int main(void)
{
    int comm_sz; //number of ranks
    int my_rank; //processes
    /*long long A[SIZE];

    for (int i = 0; i<SIZE;i++){
        A[i] = i+1;
    }*/

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    long long local=0;
    long long globalSum = 0;

    long long A[SIZE];

    for (int i = 0; i<SIZE;i++){
        A[i] = i+1;
    }    

    for (int i = my_rank*10000; i<(my_rank*10000)+10000;i++){
        local+=A[i];
    }

    MPI_Reduce(&local,&globalSum,1,MPI_LONG_LONG,MPI_SUM,0,MPI_COMM_WORLD);

    if (my_rank==0){
        printf("The summation of all numbers is: %lld",globalSum);
    }

    MPI_Finalize();
}