#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int estamosJugando = 1;
int intentosRestantes;

sem_t sem_A, sem_B, sem_C, sem_D, sem_E;

void *jugar()
{

	while (1)
	{
		// El semáforo C habilita o detiene el jugar
		sem_wait(&sem_C);

		intentosRestantes--;
		printf("jugar ");

		// Se habilita el semáforo A, que permite el paso de ganar o perder
		sem_post(&sem_A);
	}
}

void *ganar()
{

	while (1)
	{
		// El semáforo A habilita/detiene ganar o perder
		sem_wait(&sem_A);
		printf("ganar ");

		// Se habilita el semáforo B, que permite el paso a descansar
		sem_post(&sem_B);
	}
}

void *perder()
{

	while (1)
	{
		// El semáforo A habilita/detiene ganar o perder
		sem_wait(&sem_A);
		printf("perder ");

		// Se habilita el semáforo B, que permite el paso a descansar
		sem_post(&sem_B);
	}
}

void *descansar()
{

	while (1)
	{
		
		// El semáforo B habilita/detiene descansar
		sem_wait(&sem_B);
		printf("descansar.\n");

		if (intentosRestantes == 0)
		{
			// Si no quedan intentos...
			// Se habilita el semáforo D, que permite el paso de terminar
			sem_post(&sem_D);
		}
		else
		{
			// Si quedan intentos...
			// Se habilita el semáforo C, que permite el paso de jugar
			sem_post(&sem_C);
		}
	}
}

void *terminar()
{

	
	// El semáforo D habilita terminar
	sem_wait(&sem_D);
	printf("terminar\n");

}

int main(int argc, char *argv[])
{
	intentosRestantes = atoi(argv[1]);

	pthread_t h_jugar, h_ganar, h_perder, h_descansar, h_terminar;
	int id_jugar, id_ganar, id_perder, id_descansar, id_terminar;

	sem_init(&sem_A, 0, 0);
	sem_init(&sem_B, 0, 0);
	// El semaforo C que habilita el jugar, debe comenzar habilitado.
	sem_init(&sem_C, 0, 1);
	sem_init(&sem_D, 0, 0);


pthread_attr_t atributos; 
pthread_attr_init(&atributos);
struct sched_param prioridad;
pthread_attr_getschedparam(&atributos,&prioridad);
prioridad.sched_priority++;

pthread_attr_setschedparam(&atributos,&prioridad);

	id_ganar = pthread_create(&h_ganar, &atributos, ganar, (void *)NULL);
	


	id_jugar = pthread_create(&h_jugar, NULL, jugar, (void *)NULL);
	id_descansar = pthread_create(&h_descansar, NULL, descansar, (void *)NULL);
	id_terminar = pthread_create(&h_terminar, NULL, terminar, (void *)NULL);
	id_perder = pthread_create(&h_perder, NULL, perder, (void *)NULL);

	if (0 != id_jugar)
	{

		printf("\nNo se pudo crear el hilo que juega\n");
		return -1;
	}

	if (0 != id_ganar)
	{

		printf("\nNo se pudo crear el hilo que gana\n");
		return -1;
	}

	if (0 != id_perder)
	{

		printf("\nNo se pudo crear el hilo que pierde\n");
		return -1;
	}

	if (0 != id_descansar)
	{

		printf("\nNo se pudo crear el hilo que descansa\n");
		return -1;
	}

	if (0 != id_terminar)
	{

		printf("\nNo se pudo crear el hilo que termina\n");
		return -1;
	}

	// Sólo se espera por el fin de terminar
	pthread_join(h_terminar, NULL);

	sem_close(&sem_A);
	sem_close(&sem_B);
	sem_close(&sem_C);
	sem_close(&sem_D);



	return 0;
}
