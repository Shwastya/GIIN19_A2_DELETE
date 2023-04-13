#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <semaphore.h>
#include <pthread.h>
#define N 5 // Elementos en la cola de producción
/******************************************************************************
* Variables globales
******************************************************************************/
sem_t lleno; // Se inicializa a 0
sem_t vacio; // Se inicializa a N
int entrada = 0;
int salida = 0;
int buffer[N];
/******************************************************************************
* Funciones
******************************************************************************/
int producir();
void consumir();
// Productor
void *productor() {
    int i,item;
    for (i=0;i<2*N; i++) {
        item = producir();
        sem_wait(&vacio);
        buffer[entrada] = item;
        entrada = (entrada + 1) % N;
        sem_post(&lleno);
    }
}
// Consumidor
void *consumidor() {
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
int main() {
    pthread_t prod, cons;
    int rc;
    // Iniciación de los semáforos
    sem_init(&lleno, 0, 0);
    sem_init(&vacio, 0, N);
    printf("Creando hilo productor y consumidor\n");
    if ((rc=pthread_create(&prod, NULL, (void *)productor, NULL)) )
    {
    printf("Thread creation failed: %d\n", rc);
    }
    if ((rc=pthread_create(&cons, NULL, (void *)consumidor, NULL)) )
    {
    printf("Thread creation failed: %d\n", rc);
    }
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    // Destrucción de los semáforos
    sem_destroy(&lleno);
    sem_destroy(&vacio);
    return 0;
} 