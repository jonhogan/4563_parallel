//Jonathan Hogan
//mpicc -g -Wall -o inClass2 inClass2.c
//sbatch slurm.sh


#include <stdio.h>
#include <mpi.h>

#define SIZE 10000

int main(void)
{
    int comm_sz; //number of ranks
    int my_rank; //processes
    

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    long long arr[SIZE];

    for (long i = 0; i<SIZE;i++){
        arr[i]=(SIZE * my_rank)+i+1;
    }

    if (my_rank == 0){
        long long total[SIZE] = {0};
        MPI_Reduce(&arr,&total,SIZE,MPI_LONG_LONG,MPI_SUM,0,MPI_COMM_WORLD);
        long long sum = 0;
        
        for (long i = 0; i < SIZE; i++){sum += total[i];}
        
        printf("The summation of all numbers is: %lld",sum);
        
    }else{
      MPI_Reduce(&arr,NULL,SIZE,MPI_LONG_LONG,MPI_SUM,0,MPI_COMM_WORLD);
    }


    MPI_Finalize();
}