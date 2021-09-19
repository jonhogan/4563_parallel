#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void)
{
    int arr64[640000];
    int j = 1;
    int sum = 0;

    for(int i = 0; i < 640000; i++){arr64[j++];}
    for(int i = 0; i < 640000; i++){sum += arr64[i];}

    printf("%d", sum);
}

