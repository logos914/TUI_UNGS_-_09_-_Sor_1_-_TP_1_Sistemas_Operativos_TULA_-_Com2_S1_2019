#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numberArray[10000];



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


//bloque del promedio
    int sumaTotalParaPromedio = 0;
    int digitoActual;
    for (int i = 0; i < 10000; i++)
    {
        
        digitoActual = numberArray[i];
       
        sumaTotalParaPromedio+= digitoActual;
    }
    int promedio = sumaTotalParaPromedio / 10000;
    printf("\nSuma es: %d", sumaTotalParaPromedio);
    printf("\nEl promedio de entre los 10000 primeros digitos es: %d", promedio);



// bloque de contador de digitos
int sumaDigitos[10];

    for (int i = 0; i < 10; i++)
    {
        sumaDigitos[i] = 0;
    }

    for (int i = 0; i < 10000; i++)
    {
        digitoActual = numberArray[i];
        sumaDigitos[digitoActual]++;
    }

    for (int i = 0; i < 10; i++)
    {
        printf("\nEl nro %d aparece %d veces", i, sumaDigitos[i]);
    }
    


// bloque de primos
    int cantidadPrimos = 0;
    int sumaDePrimos = 0;

    for (int i = 0; i < 10000; i++)
    {
        digitoActual = numberArray[i];

        if (digitoActual == 2 || digitoActual == 3 || digitoActual == 5 || digitoActual == 7)
        {
            cantidadPrimos++;
            sumaDePrimos += digitoActual;
        }
    }

    printf("\nLa cantidad de primos es %d", cantidadPrimos);
    printf("\nLa suma de primos es %d", sumaDePrimos);

    return 0;
}