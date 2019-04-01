#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

	int numero = 0;

int main (int argc, char *argv[]) {


while (1) {
  fork();

  printf("Ahora el numero es:%d", numero);
  numero+=1;
}

	return 0;
}
