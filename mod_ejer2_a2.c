#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *functionC();
pthread_mutex_t mutex;
int counter = 0;
void main() {
    int i, j, rc1, rc2;
    pthread_t thread1, thread2;
    /* Create independent threads each of which will execute functionC */
    i=0;
    pthread_mutex_init(&mutex,NULL);
    if( (rc1=pthread_create( &thread1, NULL, functionC, (int * )&i)) )
    {
        printf("Thread creation failed: %d\n", rc1);
    }
    j=1;
    if ((rc2=pthread_create( &thread2, NULL, functionC, (int * )&j)) )
    {
        printf("Thread creation failed: %d\n", rc2);
    }
    /* Wait till threads are complete before main continues. Unless we */
    /* wait we run the risk of executing an exit which will terminate */
    /* the process and all threads before the threads have completed. */
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
    exit(0);
}
void *functionC(int *c) {
    int i;
    i = *c;
    printf("i=%d\n", i);
    // pthread_mutex_lock( &mutex);
    counter++;
    sleep(2); // para aumentar la probabilidad de una condición de carrera
    printf("Counter value: %d\n",counter);
    // pthread_mutex_unlock( &mutex);
}