#include <stdio.h>    // para usar printf
#include <stdlib.h> 	// para usar exit y funciones de la libreria standard
#include <pthread.h>    // para usar threads
#include <unistd.h> 	// para hacer sleep

/*********************/
/*********************/
#include <semaphore.h>
sem_t miSemaforo;
/*********************/
/*********************/

//para simplificar, en lugar de un archivo de verdad usaremos una variable compartida
//inicialmente tiene un valor arbitrario, podŕia ser NULL
int archivo = 500;

//tambien usaremos un array auxiliar  
char* elementos[4] = {"agua", "aire", "tierra", "fuego"};


///////////////////////////////////////////////////////
//declaro al mutex como variable global          	//  
///////////////////////////////////////////////////////
pthread_mutex_t mi_mutex;
///////////////////////////////////////////////////////


//el productor genera posiciones del 0 al 3
void* productor (void* parametro)
{   
    ///////////////////////////////////////////////////////
    //acquire()                                      	//  
    ///////////////////////////////////////////////////////
    pthread_mutex_lock(&mi_mutex);
    ///////////////////////////////////////////////////////


    //generar un numero random entre 0 y 3:
	 srand(time(NULL));
    int numero_random = rand() % 4;


    //**************************************//
    //generamos una tardanza adicional para que se produzca una condicion de carrera
    //como esta parte del código tarda, el consumidor lee la variable archivo con su valor inicial de 500
    //el resultado es un error de segmentation fault en la funcion consumidor    
    int microseconds = 1000;
  	 usleep(microseconds);  
    //**************************************//


    //escribir valor en archivo
    archivo = numero_random;


    ///////////////////////////////////////////////////////
    //release()                                      	//  
    ///////////////////////////////////////////////////////
    pthread_mutex_unlock(&mi_mutex);
    ///////////////////////////////////////////////////////
    

    /********************************/
    /********************************/
  	 sem_post(&miSemaforo);
    /********************************/
    /********************************/

    //cerrar archivo     
    pthread_exit(NULL);
}

//el consumidor lee las posiciones generadas y las usa para indexar el array elementos
void* consumidor (void* parametro)
{   
    /********************************/
    /********************************/
  	 sem_wait(&miSemaforo);
    /********************************/
    /********************************/


    ///////////////////////////////////////////////////////
    //acquire()                                      	//  
    ///////////////////////////////////////////////////////
    pthread_mutex_lock(&mi_mutex);
    ///////////////////////////////////////////////////////

    //abrir archivo para leer
    int indice = archivo;
   
    //imprimir en pantalla lo que leí
    printf("La posición %d contiene %s \n", archivo, elementos[archivo]);


    ///////////////////////////////////////////////////////
    //release()                                      	//  
    ///////////////////////////////////////////////////////
    pthread_mutex_unlock(&mi_mutex);
    ///////////////////////////////////////////////////////

    //cerrar archivo     
    pthread_exit(NULL);
}


int main ()
{
	 /****************************************************************************/
	 /****************************************************************************/
    sem_init(&miSemaforo, //se inicializa el semaforo pasado por referencia
     		 0, //tipo de semaforo 0, el semaforo es local para el proceso actual
               	//en otro caso el semaforo puede ser compartido entre procesos
     		 0);//valor inicial para el semaforo
	 /****************************************************************************/
	 /****************************************************************************/


    ///////////////////////////////////////////////////////
    // inicializo mi mutex                           	//
    ///////////////////////////////////////////////////////
    pthread_mutex_init ( &mi_mutex, NULL);
    ///////////////////////////////////////////////////////


    pthread_t p1; //una variable de tipo pthread_t sirve para identificar al hilo que se cree
    pthread_t p2;

    //craer y lanzar ambos threads                         	 
    int rc;
    rc = pthread_create(&p1, 		  	//identificador unico
   		 	NULL,		  	//atributos del thread
                        	productor,     	//funcion a ejecutar
                        	NULL);   	  	//parametros de la funcion a ejecutar, pasado por referencia
    
    rc = pthread_create(&p2,       	//identificador unico
   		 	NULL,      	//atributos del thread
                        	consumidor,	//funcion a ejecutar
                        	NULL);   		//parametros de la funcion a ejecutar, pasado por referencia


 		 if (rc){
   		 printf("Error:unable to create thread, %d \n", rc);
    		 exit(-1);
 		 }
   
    ///////////////////////////////////////////////////////
    // destruir mi mutex                           	//
    ///////////////////////////////////////////////////////
    pthread_mutex_destroy(&mi_mutex);
    ///////////////////////////////////////////////////////


   
  	 pthread_exit(NULL);
}

//Para compilar:   gcc productor-consumidor_con_mutex_y_semaforos.c -o ejecutable3 -lpthread
//Para ejecutar:   ./ejecutable3






