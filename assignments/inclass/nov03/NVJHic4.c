/*
Nathan Van De Vyvere
Jonathan Hogan
In Class 4

gcc NVJHic4.c -o NVJHic4 -pthread
sbatch ic4script

Run (Option 2)

./NVJHic4

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//958800
#define SIZE 800
#define NUM_THREADS	8
long global_sum = 0;
long N = SIZE / NUM_THREADS;
long *a,*b;
pthread_mutex_t mx;

void *sum(void *threadid)
{
    long tid;
    long lsum = 0;
    tid = (long)threadid;
    long local_n = N * tid;
    for (long i = local_n; i < local_n + N; i++){
        lsum+= a[i] + b[i];
    }
    pthread_mutex_lock(&mx);
    global_sum+=lsum;
    printf("Pthread %ld - did %ld to %ld | Local Sum = %ld | Global Sum = %ld\n",tid,local_n,local_n + N-1,lsum,global_sum);
    pthread_mutex_unlock(&mx);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   void * status;
   pthread_attr_t attr;
   pthread_mutex_init(&mx,NULL);
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   
   a = malloc(SIZE *sizeof(long));
   b = malloc(SIZE *sizeof(long));
   for (int i = 0; i < SIZE; i++){
       a[i] = i;
       b[i] = i * 2;
   }
   for(t=0;t<NUM_THREADS;t++){
        rc = pthread_create(&threads[t], &attr, sum, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    pthread_attr_destroy(&attr);

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], &status);
    }
    printf("Final global sum is: %ld",global_sum);
    pthread_mutex_destroy(&mx);
    free(a);
    free(b);
    pthread_exit(NULL);
    return 0;
}