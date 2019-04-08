// Librerias requeridas para imprimir en pantalla, ejecutar hilos concurrentemente, hacer un sleep y/o generar un nro random
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>





// La variable compartida
int numeroCompartido = 0;
int numeroCompartidoAnterior = 0;


pthread_mutex_t excluMutua; // Para controlar la lectura mientras haya modificación, o impedir la modificación mientras hay lectura



void* escritorDeNumero() {

	while(1) {

		//Escritura del nuevo numeroCompartido y resguardo del anterior.

		pthread_mutex_lock(&excluMutua);
		numeroCompartidoAnterior = numeroCompartido;
		
		numeroCompartido = rand() % 1000; 
		printf("\nsoy el escritor (%d,%d)",numeroCompartido,numeroCompartidoAnterior);
		pthread_mutex_unlock(&excluMutua);
		usleep(25000);
	}
	
}

void* lectorDeNumero() {

	
	while(1) {

		

		//Lectura del numeroCompartido y mostrar en pantalla
		pthread_mutex_lock(&excluMutua);
		

	
		printf("\nsoy el lector | El actual es: %d. El anterior es:%d\n",numeroCompartido,numeroCompartidoAnterior);
		
	
		
		pthread_mutex_unlock(&excluMutua);
		usleep(10000);
	}
	
}


int main() {

	pthread_t hiloEscritor, hiloLector;
	int id_hilo1, id_hilo2;

	pthread_mutex_init(&excluMutua, NULL);

	id_hilo2 = pthread_create(&hiloLector,NULL, lectorDeNumero,(void*) NULL);
	id_hilo1 = pthread_create(&hiloEscritor,NULL,  escritorDeNumero,(void*) NULL);
	
	
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

pthread_mutex_destroy(&excluMutua);

return 0;
}
