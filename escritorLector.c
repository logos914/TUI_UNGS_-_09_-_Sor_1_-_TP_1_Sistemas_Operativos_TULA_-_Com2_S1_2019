#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int numeroCompartido = 0;


void* escritorDeNumero() {

	while(1) {
		//Escritura del numeroCompartido

		printf("\nsoy el escritor(");
		usleep(1000);
		numeroCompartido = rand() % 1000; //
		printf("%d)\n",numeroCompartido);
		
	}
	// pthread_exit(NULL);
}

void* lectorDeNumero() {

	while(1) {
		//Lectura del numeroCompartido
		printf("\nsoy el lector: %d",numeroCompartido);
		
	}
	// pthread_exit(NULL);
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
