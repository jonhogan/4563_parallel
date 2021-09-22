#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

typedef unsigned long ulong;
#define n 640000     //Elements in the array


int main(int argc, char* argv[])
{
    ulong arr64[n];
    ulong workerArr[100000];
    ulong totalSum = 0;
    ulong processSum = 0;
    ulong rcvdElements = 0;

    int procID;
    int elemPerProc;
    int nop = 64;       //Number of processes


    for(ulong i = 0; i < 640000; i++)
    {
        arr64[i] = i + 1;
    }

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &procID);
    MPI_Comm_size(MPI_COMM_WORLD, nop);

    //Manager/Master Process
    if (procID == 0)
    {
        int index, i;
        elemPerProc = n/nop;  //Number of Elements/Numer of Processes

        if (nop > 1)
        {
            //Evenly distribute the work to the Worker/Slave Processes
            for(i = 1; i < nop - 1; i++)
            {
                index = i * elemPerProc;

                MPI_Send(&elemPerProc, 1, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
                MPI_Send(&arr64[index], elemPerProc, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
            }

            index = i * elemPerProc;
            ulong remainElements = n - index;

            MPI_Send(&remainElements, 1, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
            MPI_Send(&arr64[index], remainElements, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
        }

        for( i =0; i < elemPerProc; i++)
        {
            totalSum += arr64[i];
        }


        for(i = 1; i < nop; i++)
        {
            MPI_Recv(&processSum, 1, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD, &status);

            int sendingProc = status.MPI_SOURCE;

            totalSum += processSum;
        }
        
        printf("Total: %ld", totalSum);
    }
    //Worker processes
    else
    {
        MPI_Recv(&rcvdElements, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD, &status);

        //Store the received array
        MPI_Recv(&workerArr, rcvdElements, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD);

        //Calculate the partial sum per process
        for(int i = 0; i < rcvdElements; i++)
        {
            processSum = workerArr[i];
        }

        //Return the the sum of the process to the Manager Process
        MPI_Send(&processSum, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
    
}