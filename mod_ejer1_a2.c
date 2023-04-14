#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5 // Elementos en la cola de producción
#define N_THREADS 5 // AÑADIDO A2: define para creación de hilos

/* Variables globales */
sem_t lleno; /// Se inicializa a 0
sem_t vacio; // Se inicializa a N
int entrada = 0;
int salida = 0;
int buffer[N];

/* Funciones */
int producir();
void consumir();

void *productor() {   // Productor
    int i,item;
    for (i=0;i<2*N; i++) {
        item = producir();
        sem_wait(&vacio);
        buffer[entrada] = item;
        entrada = (entrada + 1) % N;
        sem_post(&lleno);
    }
}
void *consumidor() { // Consumidor
    int i, item;
    for (i=0;i<2*N; i++) {
        sem_wait(&lleno);
        item = buffer[salida];
        salida = (salida + 1) % N;
        sem_post(&vacio);
        consumir(item);
 }
}
// Producir
int producir() {
    printf("[+] Produciendo\n");
    return (5);
    sleep(2);
}
// Consumir
void consumir() {
    printf("[-] Consumiendo\n");
}
/******************************************************************************
* Programa principal
******************************************************************************/
int main() 
{
    // Array de IDs hilos
    pthread_t prod[N_THREADS]; 
    pthread_t cons[N_THREADS];

    int rc, i = 0;

    // Iniciación de los semáforos
    sem_init(&lleno, 0, 0);
    sem_init(&vacio, 0, N);

    // Bucle de creación de hilos
    printf("Creando hilos productores y consumidores\n");
    for (i = 0; i < N_THREADS; i++)
    {        
        if ((rc=pthread_create(&prod[i], NULL, (void *)productor, NULL)) )    
            printf("Thread creation failed: %d\n", rc);
    
        if ((rc=pthread_create(&cons[i], NULL, (void *)consumidor, NULL)) )    
            printf("Thread creation failed: %d\n", rc);    
    }
    
    // Bucle de espera de terminación de hilos
    for (i = 0; i < N_THREADS; i++)
    {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }    

    // Destrucción de los semáforos
    sem_destroy(&lleno);
    sem_destroy(&vacio);
    return 0;
} 