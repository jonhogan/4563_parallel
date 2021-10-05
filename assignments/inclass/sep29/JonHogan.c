#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main()
{
    int n = 10;  //number of processes
    int r = 0;  //Rank
    int num;


    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);

    if(r != 0)
    {
        if(r != n-1)
       { 
            r++;
            int source = r--;
            MPI_Recv(&num, 1, MPI_INT, &source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            num = num + (r*111);
            MPI_Send(&num, 1, MPI_INT, r, 0, MPI_COMM_WORLD);

       }else{
            MPI_Recv(&num, 1, MPI_INT, 8, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            num = num + (r*111);
            MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
       }

    }else{
        num = 191;
        r++;

        MPI_Send(&num,
                  1,                 //count
                  MPI_INT,           //Data Type
                  r,                 //Destination
                  0,                 //Tag
                  MPI_COMM_WORLD);

        MPI_Recv(&num, 1, MPI_INT, 9, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("%d/n", num);
    }


    MPI_Finalize;
}

