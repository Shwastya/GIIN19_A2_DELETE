from asyncio import sleep
import threading
N = 5  # Elementos en la cola de producción
# Variables globales
lleno = threading.Semaphore(0)
vacio = threading.Semaphore(N)
entrada, salida = 0, 0
buffer = [0] * N
# Funciones
def producir():
    print("[+] Produciendo")
    sleep(2)
    return 5
def consumir(item):
    print("[-] Consumiendo")
def productor():    
    global entrada # global por ser compartida
    count = 0
    while count < 2 * N:
        item = producir() # sem_wait
        vacio.acquire()
        buffer[entrada] = item
        entrada = (entrada + 1) % N
        lleno.release()  # sem_post
        count += 1
def consumidor():
    global salida # global por ser compartida 
    count = 0
    while count < 2 * N:
        lleno.acquire() # sem_wait
        item = buffer[salida]
        salida = (salida + 1) % N
        vacio.release() # sem_post
        consumir(item)
        count += 1
def main():
    prod = threading.Thread(target=productor)
    cons = threading.Thread(target=consumidor)
    print("Creando hilo productor y consumidor")
    prod.start()
    cons.start()
    prod.join()
    cons.join()

if __name__ == "__main__":
    main()
