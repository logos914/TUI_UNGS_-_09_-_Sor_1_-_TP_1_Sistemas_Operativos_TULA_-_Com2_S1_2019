// Librerias requeridas para imprimir en pantalla, ejecutar hilos concurrentemente, hacer un sleep y/o generar un nro random
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>




// La variable compartida
int numeroCompartido = 0;
int numeroCompartidoAnterior = 0;
int lectoresEnSimultaneo = 0;
int numerodeHiloTotales;

pthread_mutex_t excluMutua; // Impide cualquier tipo de operación de lectura/escritura de las vars compartidas
sem_t semaforosLectura; // Asiste en la modificación controlada de lectoresEnSimultaneo;


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

void* lectorDeNumero(void *arg) {

	int lectorActualenSimultaneo = 0;
	int hilonro = 0;
	while(1) {

		
		sem_wait(&semaforosLectura);
		if (hilonro == 0) {
			numerodeHiloTotales++;
			hilonro = numerodeHiloTotales;
		}

		lectoresEnSimultaneo++;
		lectorActualenSimultaneo = lectoresEnSimultaneo;

		if (lectoresEnSimultaneo == 1) {
			pthread_mutex_lock(&excluMutua);
		}

		sem_post(&semaforosLectura);

		//Lectura del numeroCompartido y mostrar en pantalla
		
		printf("\nSoy el hilo %d y el lector %d | El actual es: %d. El anterior es:%d\n",
		hilonro, lectorActualenSimultaneo, numeroCompartido,numeroCompartidoAnterior);

		sem_wait(&semaforosLectura);
		lectoresEnSimultaneo= lectoresEnSimultaneo - 1;


		if (lectoresEnSimultaneo == 0) {
			pthread_mutex_unlock(&excluMutua);
		}	
		sem_post(&semaforosLectura);
		
		usleep(5000);
	}
	
}


int main() {

	pthread_t hiloEscritor, hiloLector1, hiloLector2, hiloLector3;
	int id_hilo1, id_hilo2, id_hilo3, id_hilo4;


	pthread_mutex_init(&excluMutua, NULL);
	sem_init(&semaforosLectura, 0,1);


	id_hilo2 = pthread_create(&hiloLector1,NULL, lectorDeNumero,(void*) NULL);
	id_hilo3 = pthread_create(&hiloLector2,NULL, lectorDeNumero,(void*) NULL);
	id_hilo4 = pthread_create(&hiloLector3,NULL, lectorDeNumero,(void*) NULL);
	id_hilo1 = pthread_create(&hiloEscritor,NULL,  escritorDeNumero,(void*) NULL);
	
	
	if (0 != id_hilo1 ) {

		printf("\nNo se pudo crear el hilo escritor\n");
		return -1;
	} 

	

	if (0 != id_hilo2) {

			printf("\nNo se pudo crear el hilo lector\n");
			return -1;
		}

	if (0 != id_hilo3 ) {

		printf("\nNo se pudo crear el hilo lector\n");
		return -1;
	} 

	if (0 != id_hilo4 ) {

		printf("\nNo se pudo crear el hilo lector\n");
		return -1;
	} 


pthread_join(hiloEscritor , NULL);

pthread_join(hiloLector1 , NULL);
pthread_join(hiloLector2 , NULL);
pthread_join(hiloLector3 , NULL);

pthread_mutex_destroy(&excluMutua);

return 0;
}
