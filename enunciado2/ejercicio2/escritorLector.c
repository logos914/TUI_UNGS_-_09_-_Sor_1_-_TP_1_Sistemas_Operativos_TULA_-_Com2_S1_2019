// Librerias requeridas para imprimir en pantalla, ejecutar hilos concurrentemente, hacer un sleep y/o generar un nro random
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


// La variable compartida
int numeroCompartido = 0;
int numeroCompartidoAnterior = 0;


void* escritorDeNumero() {

	while(1) {
		//Escritura del nuevo numeroCompartido y resguardo del anterior.

		numeroCompartidoAnterior = numeroCompartido;
		usleep(500);
		numeroCompartido = rand() % 1000; 
		printf("\nsoy el escritor (%d,%d)",numeroCompartido,numeroCompartidoAnterior);
		
	}
	
}

void* lectorDeNumero() {

	while(1) {

		//Lectura del numeroCompartido y mostrar en pantalla
		printf("\nsoy el lector | El actual es: %d. El anterior es:%d",numeroCompartido,numeroCompartidoAnterior);
		
	}
	
}


int main() {

	pthread_t hiloEscritor, hiloLector;
	int id_hilo1, id_hilo2;
	id_hilo1 = pthread_create(&hiloEscritor,NULL,  escritorDeNumero,(void*) NULL);
	id_hilo2 = pthread_create(&hiloLector,NULL, lectorDeNumero,(void*) NULL);
	
	if (0 != id_hilo1 ) {

		printf("\nNo se pudo crear el hilo escritor\n");
		return -1;
	} 

	

	if (0 != id_hilo2) {

			printf("\nNo se pudo crear el hilo lector\n");
			return -1;
		}


pthread_join(hiloEscritor , NULL);

pthread_join(hiloLector , NULL);

}
