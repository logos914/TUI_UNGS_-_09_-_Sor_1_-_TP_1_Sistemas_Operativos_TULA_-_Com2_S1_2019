#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_mutex_t excluMutua; // Impide cualquier tipo de operación de lectura/escritura de las vars compartidas
int numberArray[10000];


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



int main(){

  FILE *myFile;
  myFile = fopen("10milDigitosDePi_separados.txt", "r");

  //leer archivo en un array
 
  int i;

  if (myFile == NULL){
    printf("Error en la lectura\n");
    exit (0);
  }

  for (i = 0; i < 10000; i++){
    fscanf(myFile, "%d,", &numberArray[i] );
  }
  fclose(myFile);



    pthread_t hiloEscritor, hiloLector;
	int id_hilo1, id_hilo2, id_hilo3, id_hilo4;




  return 0;
}