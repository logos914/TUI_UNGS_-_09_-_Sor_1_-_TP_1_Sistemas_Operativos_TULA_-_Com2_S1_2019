#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t excluMutua; // Impide cualquier tipo de operación de lectura/escritura de las vars compartidas
int numberArray[10000];

void *promedio()
{
    int sumaTotalParaPromedio = 0;
    int digitoActual;
    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&excluMutua);
        digitoActual = numberArray[i];
        pthread_mutex_unlock(&excluMutua);
        sumaTotalParaPromedio+= digitoActual;
    }
    int promedio = sumaTotalParaPromedio / 10000;
    printf("\nSuma es: %d", sumaTotalParaPromedio);
    printf("\nEl promedio de entre los 10000 primeros digitos es: %d", promedio);
}

void *contadorDeDigitos()
{

    int sumaDigitos[10];
    int digitoActual;

    for (int i = 0; i < 10; i++)
    {
        sumaDigitos[i] = 0;
    }

    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&excluMutua);
        digitoActual = numberArray[i];
        sumaDigitos[digitoActual]++;
        pthread_mutex_unlock(&excluMutua);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&excluMutua);
        printf("\nEl nro %d aparece %d veces", i, sumaDigitos[i]);
        pthread_mutex_unlock(&excluMutua);
    }
}

void *primos()
{

    int cantidadPrimos = 0;
    int sumaDePrimos = 0;
    int digitoActual;

    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&excluMutua);
        digitoActual = numberArray[i];
        pthread_mutex_unlock(&excluMutua);

        if (digitoActual == 2 || digitoActual == 3 || digitoActual == 5 || digitoActual == 7)
        {
            cantidadPrimos++;
            sumaDePrimos += digitoActual;
        }
    }

    pthread_mutex_lock(&excluMutua);
    printf("\nLa cantidad de primos es %d", cantidadPrimos);
    printf("\nLa suma de primos es %d", sumaDePrimos);
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

    pthread_t prom, cont, prim;
    pthread_create(&prom, NULL, promedio, NULL);
    pthread_create(&cont, NULL, contadorDeDigitos, NULL);
    pthread_create(&prim, NULL, primos, NULL);

    pthread_join(prom, NULL);
    pthread_join(cont, NULL);
    pthread_join(prim, NULL);

    pthread_mutex_destroy(&excluMutua);
    

    return 0;
}