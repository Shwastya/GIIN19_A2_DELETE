#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAXTHREADS 2
void *functionC1();
void *functionC2();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER,
 mutex2 = PTHREAD_MUTEX_INITIALIZER;
int counter1 = 0;
int counter2 = 0;
int i;
void main()
{
 int rc1, rc2;
 pthread_t threads1[MAXTHREADS], threads2[MAXTHREADS];
 /* Create independent threads each of which will execute functionC */
 for (i = 0; i < MAXTHREADS; i ++)
 if( (rc1=pthread_create( &threads1[i], NULL, functionC1, NULL)) )
 {
 printf("Thread creation failed: %d\n", rc1);
 }
 for (i = 0; i < MAXTHREADS; i ++)
 if( (rc2=pthread_create( &threads2[i], NULL, functionC2, NULL)) )
 {
 printf("Thread creation failed: %d\n", rc2);
 }
 /* Wait till threads are complete before main continues. Unless we */
 /* wait we run the risk of executing an exit which will terminate */
 /* the process and all threads before the threads have completed. */
 for (i = 0; i < MAXTHREADS; i ++)
 pthread_join( threads1[i], NULL);
 for (i = 0; i < MAXTHREADS; i ++)
 pthread_join( threads2[i], NULL);
exit(0); }
void *functionC1()
{
 pthread_mutex_lock( &mutex1 );
 counter1++;
 printf("Counter1 value: %d\n",counter1);
 pthread_mutex_unlock( &mutex1 );
}
void *functionC2()
{
 pthread_mutex_lock( &mutex2 );
 counter2=counter2+2;
 printf("Counter2 value: %d\n",counter2);
 pthread_mutex_unlock( &mutex2 );
} 