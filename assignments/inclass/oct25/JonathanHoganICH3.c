//Jonathan Hogan
//mpicc -g -Wall -o JHIC3 JonathanHoganICH3.c
//sbatch slurm.sh


#include <stdio.h>
#include <mpi.h>

#define SIZE 16000

int main(void)
{
    int comm_sz; //number of ranks
    int my_rank; //processes
    long i = 0;  //counter
    

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    long long *bigArray;
    long long smallArray[SIZE/comm_sz];

    if (my_rank == 0){
        bigArray[SIZE] = malloc(SIZE);
        long long locSum = 0;

        for (long i = 0; i < SIZE; i++){
            bigArray[i] = i+1;
        }
        
        MPI_Scatter(&smallArray, (SIZE/comm_sz), MPI_LONG_LONG, &smallArray,(SIZE/comm_sz), MPI_LONG_LONG, 0, MPI_COMM_WORLD);

      
        for (i = 0; i < (SIZE/comm_sz); i++){
            locSum += smallArray[i];
        }
        printf("This is process %d. Summation of all my elements is: %lld\n", my_rank, locSum);

        
    }else{
        long long locSum = 0;

        MPI_Scatter(&smallArray, (SIZE/comm_sz), MPI_LONG_LONG, &smallArray,(SIZE/comm_sz), MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        
        for (i = 0; i < (SIZE/comm_sz); i++){
            locSum += smallArray[i];
        }

        printf("This is process %d. Summation of all my elements is: %lld\n", my_rank, locSum);
    }


    MPI_Finalize();
}

/*#include <stdio.h>
#include <mpi.h>

#define LENGTH 16000
#define SIZE 1000

int main(void)
{
    int comm_sz; //number of ranks
    int my_rank; //processes

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int smallArray[SIZE];
    int sum = 0;
    if (my_rank == 0){
        int bigArray[LENGTH];
        for (int i = 0; i < LENGTH; i++){
            bigArray[i]=i+1;
        }
        MPI_Scatter(&bigArray,SIZE,MPI_INT,&smallArray,SIZE,MPI_INT,0,MPI_COMM_WORLD);
        for (int i = 0; i < SIZE; i++){
            sum += smallArray[i];
        }
        printf("This is process 0. Summation of all my elements is: %d\n",sum);
    }

    else{
        MPI_Scatter(NULL,LENGTH,MPI_INT,&smallArray,SIZE,MPI_INT,0,MPI_COMM_WORLD);
        for(int i = 0; i < SIZE; i++){
            sum += smallArray[i];
        }
        printf("This is process %d. Summation of all my elements is: %d\n",my_rank,sum);
    }

    MPI_Finalize();
}
*/