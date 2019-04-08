#include <stdio.h>
#include <stdlib.h>

//compilar con gcc experimentoPi.c -o ejecutable
//ejecutar con  ./ejecutable

int main()
{

    FILE *myFile;
    myFile = fopen("10milDigitosDePi_separados.txt", "r");

    //leer archivo en un array
    int numberArray[10000];
    int i;
    int sumaDeDigitos = 0;

    if (myFile == NULL)
    {
        printf("Error en la lectura\n");
        exit(0);
    }

    for (i = 0; i < 10000; i++)
    {
        fscanf(myFile, "%d,", &numberArray[i]);
        sumaDeDigitos+= numberArray[i];
    }
    fclose(myFile);


    
    printf("La suma es:%d\n",sumaDeDigitos);
    return 0;
}