#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define CANTIDAD_HILOS 5
pthread_mutex_t excluMutua; // Impide cualquier tipo de operación de lectura/escritura de las vars compartidas
int numberArray[10000];
int bloquespendientes = CANTIDAD_HILOS;
int sumaTotal = 0;

void *sumador()
{

    int segmentoASumar[10000 / CANTIDAD_HILOS];
    pthread_mutex_lock(&excluMutua);
    int indiceLocal = 0;
    int sumaLocal = 0;
    for (int i = (10000 / CANTIDAD_HILOS) * (bloquespendientes - 1); i < (10000 / CANTIDAD_HILOS) * bloquespendientes; i++)
    {
        segmentoASumar[indiceLocal] = numberArray[i];
        
        indiceLocal++;
    }
    bloquespendientes--;
    pthread_mutex_unlock(&excluMutua);

    for (int i = 0; i < 10000 / CANTIDAD_HILOS; i++)
    {
        
        sumaLocal = sumaLocal + segmentoASumar[i];
    }

    printf("\nsumamos localmente: %d\n",sumaLocal);
    pthread_mutex_lock(&excluMutua);
    sumaTotal = sumaTotal + sumaLocal;
    pthread_mutex_unlock(&excluMutua);
}

int main()
{

    FILE *myFile;
    myFile = fopen("10milDigitosDePi_separados.txt", "r");

    //leer archivo en un array

    int i;

    if (myFile == NULL)
    {
        printf("Error en la lectura\n");
        exit(0);
    }

    for (i = 0; i < 10000; i++)
    {
        fscanf(myFile, "%d,", &numberArray[i]);
    }
    fclose(myFile);

    pthread_mutex_init(&excluMutua, NULL);
    
    for (int h = 0; h < CANTIDAD_HILOS; h++) {

        pthread_t tid;
        pthread_create(&tid, NULL, sumador, NULL);
        pthread_join(tid,NULL);
    }

    


    

    pthread_mutex_destroy(&excluMutua);
    printf("La suma total es: %d", sumaTotal);

    return 0;
}