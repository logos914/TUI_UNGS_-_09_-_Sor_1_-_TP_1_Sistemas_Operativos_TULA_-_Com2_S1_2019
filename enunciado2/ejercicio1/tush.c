#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10

int SeContinuaEjecutando(char *, char *);
void imprimirEncabezadTush();
void parseCmd(char*, char**);

  int main(void) {

  pid_t pid;
  char cmd[MAX_COMMAND_LENGTH];
  char comandoDeSalida[] = "salir";
  int ejecucion = 1;
  imprimirEncabezadoTush();

  while(ejecucion) {




	  printf("t$_: ");
	  fgets(cmd, sizeof(cmd), stdin);

	  //remover el enter de tu comando
	  if(cmd[strlen(cmd)-1] == '\n') {
	    	cmd[strlen(cmd)-1] = '\0';
	  }



	  if (SeContinuaEjecutando(comandoDeSalida,cmd)) {

		  printf("========================\nEjecutando: %s\n", cmd);

		  char* params[MAX_NUMBER_OF_PARAMS + 1];
		  parseCmd(cmd, params);

		  pid = fork();

		  if (pid == 0) {
			  //Proceso hijo, para ejecutar el comando solicitado
			  printf("\n");
			  execvp(params[0], params);
		  }
		  wait(NULL);


	  } else {
		  ejecucion = 0;
	  }








  }




  printf("\nGracias por usar Tush!\nEl intérprete Tulaico de la shell");





  return 0;
}


int SeContinuaEjecutando(char *comandoDeSalida, char *cmd) {

		for(int i = 0; i < sizeof(*comandoDeSalida); i++ ) {
				if (comandoDeSalida[i] != cmd[i]) {

				// para debug:	printf("%d y %d \n",comandoDeSalida[i],cmd[i]);
					return 1;
				}
			}
		return 0;



}

void imprimirEncabezadoTush() {
	printf(" _________  __  __   ______   ___   ___   __       \n");
	printf("/________/\\/_/\\/_/\\ /_____/\\ /__/\\ /__/\\ /__/\\     \n");
	printf("\\__.::.__\\/\\:\\ \\:\\ \\\\::::_\\/_\\::\\ \\\\  \\ \\\\.:\\ \\    \n");
	printf("   \\::\\ \\   \\:\\ \\:\\ \\\\:\\/___/\\\\::\\/_\\ .\\ \\\\::\\ \\   \n");
	printf("    \\::\\ \\   \\:\\ \\:\\ \\\\_::._\\:\\\\:: ___::\\ \\\\__\\/_  \n");
	printf("     \\::\\ \\   \\:\\_\\:\\ \\ /____\\:\\\\: \\ \\\\::\\ \\ /__/\\ \n");
	printf("      \\__\\/    \\_____\\/ \\_____\\/ \\__\\/ \\::\\/ \\__\\/ \n");
	printf("                                                   \n");


}

void parseCmd(char* cmd, char** params)
{
  for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
	params[i] = strsep(&cmd, " ");
	if(params[i] == NULL) break;
  }
}

