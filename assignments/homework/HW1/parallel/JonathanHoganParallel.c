#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

typedef unsigned long ulong;
#define n 640000     //Elements in the array
#define nop 64       //Number of processes

int main(int argc, char* argv[])
{
    ulong arr64[n];
    ulong totalSum = 0;
    ulong processSum = 0;

    int procID;
    int elemPerProc;


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
            for(i = 1; i < nop -1; i++)
            {
                
            }
        }
    }
    

    printf("%ld", totalSum);
}