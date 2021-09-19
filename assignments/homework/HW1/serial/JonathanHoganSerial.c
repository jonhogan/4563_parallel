#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

typedef unsigned long ulong;

int main(void)
{
    ulong arr64[640000];
    ulong j = 1;
    ulong sum = 0;

    for(ulong i = 0; i < 640000; i++)
    {
        arr64[i] = j;
        j++;
    }
    for(ulong i = 0; i < 640000; i++){sum += arr64[i];}

    printf("%ld", sum);
}

