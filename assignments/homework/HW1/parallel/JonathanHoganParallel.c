/***************************************************************************


Name: Jonathan Hogan 
Course: CMPS 4563
Due: 09/22/21 - 0800

Assignment 1

Description:

    Part 1: Sequential program to visit and sum all elements in an array
            with a size of 640,000 elements.

    Part 2: Rewrite the program using Parallel methologies, 64 processes

    Time both.
***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#define n 640000     //Elements in the array



int main(void)
{
    int procID = 0;                     //Process ID/Rank
    int procNum = 64;                   //Number of processes
    int retElements = 0;                //Elements returned
    int elemPerProc = n/procNum;        //Number of elements passed to each process

    double start, end;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procID);
    

    long long tempArr[elemPerProc];
    start = MPI_Wtime();

    if (procID == 0)
    {
        int index;
        int i;

        long long arr64[n];

        for (i = 0; i < n; i++)
        {
            //Fill the array with the numbers 1 to 640,000
            arr64[i] = i + 1;
        }

        for (i = 1; i < procNum; i++)
        {
            for (int j = 0; j < (j+1)*elemPerProc; j++)
            {
                tempArr[j] = j*elemPerProc;
            }

            index = i*elemPerProc;

            MPI_Send(&elemPerProc,
                     1,                 //count
                     MPI_LONG_LONG,     //Data Type
                     i,                 //Destination
                     0,                 //Tag
                     MPI_COMM_WORLD);

            MPI_Send(tempArr,
                     1,                 //count
                     MPI_LONG_LONG,     //Data Type
                     i,                 //Destination
                     1,                 //Tag
                     MPI_COMM_WORLD);
        }

        index = i*elemPerProc;

        int remainingElements = n - index;
        
        MPI_Send(&remainingElements,
                 1,                 //count
                 MPI_LONG_LONG,     //Data Type
                 i,                 //Destination
                 0,                 //Tag
                 MPI_COMM_WORLD);

        MPI_Send(&arr64[index],
                 1,                 //count
                 MPI_LONG_LONG,     //Data Type
                 i,                 //Destination
                 0,                 //Tag
                 MPI_COMM_WORLD);

        long long totalSum = 0;

        for (i = 0; i < elemPerProc; i++)
        {
            totalSum += arr64[i];
        }

        //Manager Process receives partial sums from Worker Processes
        long long temp;

        for (i = 1; i < elemPerProc; i++)
        {
            MPI_Recv(&temp,
                     1,                 //count
                     MPI_LONG_LONG,     //Data Type
                     i,                 //Destination
                     0,                 //Tag
                     MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            
            totalSum += temp;
        }

        end = MPI_Wtime();

        printf("Total: %lld", totalSum);
        printf("Time elapsed: %f", end - start);

    }
    else
    {
        MPI_Recv(&elemPerProc,
                 1,                 //count
                 MPI_LONG_LONG,     //Data Type
                 0,                 //Destination
                 0,                 //Tag
                 MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        MPI_Recv(tempArr,
                 retElements,
                 MPI_LONG_LONG,
                 0,
                 1,
                 MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        long long processSum = 0;

        //Sum for each process
        for (int i = 0; i < retElements; i++)
        {
            processSum =+ tempArr[i];
        }

        //Return the process sums to the Manager Process
        MPI_Send(&processSum,
                 1,
                 MPI_LONG_LONG,
                 0,
                 0,
                 MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

    