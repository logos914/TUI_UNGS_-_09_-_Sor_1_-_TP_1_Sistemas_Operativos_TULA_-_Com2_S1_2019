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
	//	printf("[jugar]");
		sem_wait(&sem_C);
	
		intentosRestantes--;
		printf("jugar ");
		
		sem_post(&sem_A);
			

	}

	
}

void *ganar()
{

	while (1)
	{
		
		sem_wait(&sem_A);
		printf("ganar ");
		sem_post(&sem_B);
	}
}

void *perder()
{

	while (1)
	{
		
		sem_wait(&sem_A);
		printf("perder ");
		sem_post(&sem_B);
	}
}

void *descansar()
{

	while (1)
	{
		//printf("[descansar]");


		sem_wait(&sem_B);
			
			printf("descansar.\n");
			

		if (intentosRestantes == 0) {
			
		
			sem_post(&sem_D);
			
			
		} else {
sem_post(&sem_C);
		}
		
		

		
	}
}

void *terminar()
{

	
	//printf("[terminar]");

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
	sem_init(&sem_C, 0, 1);
	sem_init(&sem_D, 0, 0);
	sem_init(&sem_E, 0, 0);

id_ganar = pthread_create(&h_ganar, NULL, ganar, (void *)NULL);
id_perder = pthread_create(&h_perder, NULL, perder, (void *)NULL);
id_jugar = pthread_create(&h_jugar, NULL, jugar, (void *)NULL);
id_descansar = pthread_create(&h_descansar, NULL, descansar, (void *)NULL);
id_terminar = pthread_create(&h_terminar, NULL, terminar, (void *)NULL);







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


	pthread_join(h_terminar, NULL);



	// pthread_mutex_destroy(&excluMutua);

	return 0;
}
