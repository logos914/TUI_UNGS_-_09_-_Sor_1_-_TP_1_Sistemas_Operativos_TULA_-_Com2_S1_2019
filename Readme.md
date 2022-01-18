


**Universidad Nacional de General Sarmiento**


**Sistemas Operativos y Redes I**

**Comisión 2 Mañana**


![](Aspose.Words.0dda17db-1f40-446c-8e6d-2916bdcd691e.001.png)



**Trabajo Práctico**


**Sistemas Operativos y Redes I**

**TP1 1er Cuatrimestre 2019**


**Andrés Rojas Paredes**

**Hvara Ocar**



|**APELLIDO Y NOMBRE**|<p>**LEGAJO**</p><p>		</p>|<p>**EMAIL**</p><p>		</p>|
| :- | :- | :- |
|Tula, Ignacio Mariano|<p>35.226.620/2014</p><p></p>|itula@logos.net.ar<br>itula@ungs.edu.ar|



**1era Parte
Shell**
============
## **Ejercicio 1. Sistema Operativo GNU/Linux**
### Inciso 1

Se instaló Ubuntu 18.10 en la notebook personal del estudiante, y una versión en un pendrive USB con persistencia.

El único inconveniente detectado es que se prefirió Ubuntu por sobre Debian, puesto que en esta última distribución existían problemas con los controladores de los adaptadores de red y de gráficos.

En ambas instalaciones, se ejecutó los comandos que quedaron descritos en un archivo bash ubicado en ***/home/sor\_user/tp1/proyectosot1ungstula/ejercicio1.sh***




|#!/bin/bash                                                                    <br>sudo adduser sor\_user sudo                        # inciso 2<br>su sor\_user                                       # inciso 3                          <br>sudo apt-get update                               # inciso 3                                                    <br>sudo apt-get install gcc vim nano gedit emacs git # inciso 4|
| :- |
## **Ejercicio 2. Shell y Supermenu**

**Inciso 1**

Se creó el archivo ***supermenu.sh*** en ***/home/sor\_user/tp1/proyectosot1ungstula* .**

**Inciso 2**

Se creó en Gitlab el proyecto ubicado en la ruta:[ ](https://gitlab.com/itula/proyectosor1ungstula)<https://gitlab.com/itula/proyectosor1ungstula>

[](https://gitlab.com/itula/proyectosor1ungstula)

[](https://gitlab.com/itula/proyectosor1ungstula)

El cual se clonó en la ubicación ***/home/sor\_user/tp1/*** mediante el comando:


|git clone https://gitlab.com/itula/proyectosor1ungstula.git|
| :- |


Se modificó la variable del archivo ***supermenu.sh***


|proyectoActual="/home/sor\_user/tp1/proyectosor1ungstula"|
| :- |

Es decir que se incluyó el propio supermenu dentro del proyecto de Gitlab.

Fue necesario ejecutar en consola también:


|git config --global user.email "itula@logos.net.ar"<br>git config --global user.name "Ignacio Tula"|
| :- |

**Inciso 3**

Para agregar una opción nueva en el ***supermenu.sh*** es necesario realizar tres modificaciones en el código fuente. A saber:

1. En la definición de la función “*imprimir\_menu*“ se debe agregar una cadena de caracteres que es el texto que leerá el usuario para comprender qué letra debe presionar para realizar determinada tarea.


|**35.** echo -e "\t\t\t p.  Mostrar PCB de proceso";|
| :- |

2. Agregar una posibilidad dentro del *case* del bloque de la “*lógica principal”* que detecte el carácter asignado a la determinada tarea para que ejecute una función.


|**181.** p|P) p\_funcion;;|
| :- |

2. Agregar la definición de la función que es llamada en el case del item 2.


|**p\_funcion** () {<br>`    `imprimir\_encabezado "\tOpción p. Mostrar PCB";<br>`		`echo -e "Vamos a ejecutar TOP, para que elija el PID que quiere analizar."<br>`		`decidir "top";<br>`		`imprimir\_encabezado "\tOpción p. Mostrar PCB";<br>`		`echo -e "Indique el PID del cual desea conocer su PCB";<br>`		`read pcb;<br>`		`post\_p\_funcion $pcb;<br>`   `}<br><br>**post\_p\_funcion**() {<br>`    `imprimir\_encabezado "\tOpción p. Mostrar PCB";<br>`     `decidir "cat /proc/$1/status | grep 'Name\|Pid\|Ppid\|State\| voluntary\_ctxt\_swi tches\|nonvoluntary\_ctxt\_switches'";<br>}|
| :- |

En este ejercicio en particular se decidió que se ejecuten en dos funciones. Una primera que permitiera ver todos los procesos con *TOP*  y una segunda que al ser finalizado *TOP*  preguntara por el *PID* que se deseaba conocer.

**2da Parte
Procesos y Semáforos**
======================
## **Ejercicio 1. Procesos y Fork**
### Inciso 1


|1. #include <stdio.h><br>2. #include <sys/types.h><br>3. #include <unistd.h><br>4. <br>5. int main() {<br>6.   fork();<br>7.<br>8.  printf("Hola Mundo!\n");<br>9.<br>10.  **return** 0;<br>11. }|
| :- |

Este programa emitirá dos líneas de texto en la consola expresando “Hola Mundo!". Esto es debido a que un printf es ejecutado por el proceso principal, y otro por el proceso hijo que es llamado a través de fork(). Al no existir una estructura de control, ni una variable sobre la cual reconocer el pid del proceso actual, ambos procesos (padre e hijo) ejecutarán lo mismo, desde la línea 7 en adelante.

###
### Inciso 2. proyectosor1ungstula/enunciado2/ejercicio1/bombafork.c


|<p>#include <sys/wait.h><br>#include <unistd.h><br>#include <stdio.h><br>#include <stdlib.h><br><br>int numero = 0;<br><br>int main (int argc, char \*argv[]) {<br><br><br>**while** (1) {<br>  </p><p>`  `fork();<br><br>`  `printf("Ahora el numero es:%d \n", numero);<br>`  `numero+=1;<br>}<br><br>`	`**return** 0;<br>}</p>|
| :- |
||

En las ejecuciones realizadas no se ha encontrado límite alguno para la creación de procesos, o al menos no se ha tocado el límite que pueda tener el Sistema Operativo. También su medición es complicada, considerando que la computadora deja de ser capaz de mostrar otras aplicaciones de monitoreo del procesador y memoria, hasta el punto de tildarse por falta de memoria RAM principal disponible.

### Inciso 3. proyectosor1ungstula/enunciado2/ejercicio1/tush.c

Se creó “Tush” el intérprete de comandos shell de Tula.

## **Ejercicio 2. Threads y semáforos**
### Inciso 1. proyectosor1ungstula/enunciado2/ejercicio2/escritorLector.c

Se implementó un programa que posee 2 hilos, uno para escritura y otro para lectura. Comparten dos variables. Una llamada numeroActual, que sirve para almacenar un número que se obtiene por medio del azar. Y otra variable adicional que guarda el número anterior seleccionado por el azar.
### Inciso 2

Ambos hilos, por una cuestión para facilitar la interpretación de este trabajo muestran un texto en pantalla, indicando si el mismo es el escritor o el lector, y luego las variables compartidas.

La condición de carrera entre los hilos existe en el momento en el cual el escritor se encuentra en el proceso de modificar ambas variables. Si el escritor al reemplazar la variable del número anterior por el actual, es interrumpido allí por el planificador del sistema operativo, y se ejecuta el hilo lector este mismo leerá el mismo valor en ambas variables.

Suponiendo una secuencia de números: 1 -> 3 -> 8 -> 5

Se esperaría que un proceso lector muestre (suponiendo que se ejecuta siempre que un escritor haya finalizado).


|Soy el lector | El actual es: 1. El anterior es: 0 <br>Soy el lector | El actual es: 3. El anterior es: 1 <br>Soy el lector | El actual es: 8. El anterior es: 3 <br>Soy el lector | El actual es: 5. El anterior es: 8|
| :- |

Pero si no se puede controlar la secuencia de ejecución, pueden ocurrir anomalías como estas:


|Soy el lector | El actual es: 1. El anterior es: 0 <br>Soy el lector | El actual es: 1. El anterior es: 1 <br>Soy el lector | El actual es: 3. El anterior es: 1 <br>Soy el lector | El actual es: 5. El anterior es: 8|
| :- |


De forma igual pero inversa, el lector puede ser interrumpido por el planificador mientras obtuvo de memoria el valor actual, pero aún sin conseguir el valor anterior. Si durante esta interrupción, un escritor se ejecutase completamente, pueden ocurrir nuevas situaciones no deseadas como la anterior.

###
### Inciso 3


|<p>**void**\* **escritorDeNumero**() {<br><br>`    `**while**(1) {<br>       <br><br>`        `// INICIO DE LA SECCIÓN CRÍTICA<br>`        `numeroCompartidoAnterior = numeroCompartido;<br>`        `usleep(500);<br>`        `numeroCompartido = rand() % 1000;<br>`     `printf("\nsoy el escritor    (%d,%d)",</p><p>`           `numeroCompartido, numeroCompartidoAnterior);   </p><p>`        `// FIN DE LA SECCIÓN CRÍTICA</p><p>     <br>`    `}<br>    <br>}</p>|
| :- |



|<p>**void**\* **lectorDeNumero**() {<br><br>`    `**while**(1) {<br><br>`        `// INICIO DE LA SECCIÓN CRÍTICA<br>`        `printf("\nsoy el lector | El actual es: %d. El anterior es:%d", numeroCompartido, numeroCompartidoAnterior);<br>`       `// FIN DE LA SECCIÓN CRÍTICA</p><p><br>`    `}<br>    <br>}</p>|
| :- |


### Inciso 4. proyectosor1ungstula/enunciado2/ejercicio2/escritorLectorMutex.c

Una forma sencilla de resolver el problema con mutex es:


|**pthread\_mutex\_t** excluMutua; // Para controlar la lectura mientras haya modificación, o impedir la modificación mientras hay lectura|
| :- |


|<p>**void**\* **escritorDeNumero**() {<br><br>`    `**while**(1) {<br><br>`        `//Escritura del nuevo numeroCompartido y resguardo del anterior.<br><br>`        `pthread\_mutex\_lock(&excluMutua);<br>`        `numeroCompartidoAnterior = numeroCompartido;<br>        <br>`        `numeroCompartido = rand() % 1000;<br>`        `printf("\nsoy el escritor   (%d,%d)",</p><p>`               `numeroCompartido, numeroCompartidoAnterior);<br>`        `pthread\_mutex\_unlock(&excluMutua);<br>`        `usleep(25000);<br>`    `}<br>    <br>}<br><br>**void**\* **lectorDeNumero**() {<br><br>    <br>`    `**while**(1) {<br><br>        <br><br>`        `//Lectura del numeroCompartido y mostrar en pantalla<br>`        `pthread\_mutex\_lock(&excluMutua);<br>        </p><p>`        `printf("\nsoy el lector | El actual es: %d. El anterior es:%d\n",</p><p>`              `numeroCompartido, numeroCompartidoAnterior);<br>        <br>`        `pthread\_mutex\_unlock(&excluMutua);<br>`        `usleep(10000);<br>`    `}<br>    <br>}</p>|
| :- |
||

Ahora bien, para una ejecución simultánea de un único hilo lector y un único hilo escritor  se ha encontrado que esta solución funciona, pero si sería necesario agregar semáforos de sincronización para poder ejecutar m hilos de lectura  y n hilos de escritura.

Se implementa esta solución en el archivo proyectosor1ungstula/enunciado2/ejercicio2/escritorLectorSemaforos.c

### Inciso 5. proyectosor1ungstula/enunciado2/ejercicio2/juegoDeLaVida.c

### Inciso 6. proyectosor1ungstula/enunciado2/ejercicio2/outputJuegoDeLaVida.txt

Se guardó el output de la ejecución con un parámetro de 500. No existe el azar, los resultados “ganar” y “perder” se van alternando en una secuencia que comienza por el primer hilo en ser ejecutado.

Esto ocurre porque una vez que “ganar” encontró habilitado su semáforo primero (antes que “perder”), para cuando vuelve a comenzar y esperar por el mismo semáforo, quien está ahora en la cola primero es perder.


sem\_A



bloqueo

**PERDER**

**GANAR**



![](Aspose.Words.0dda17db-1f40-446c-8e6d-2916bdcd691e.002.png)

### Inciso 7.
No existen rachas ganadoras o perdedoras, la justicia que imparte el planificador de procesos es tal que permite que sus ejecuciones sean alternadas, a tal punto que apenas queda habilitado el semáforo *sem\_A,* es entregado a quien continúa primero en la lista de pendiente o de hilos bloqueados por el semáforo.

### Inciso 8. proyectosor1ungstula/enunciado2/ejercicio2/juegoDeLaVidaBienJugado.c
El agregar prioridad al hilo ganador, modifica levemente el resultado, pero solo luego de muchas repeticiones (se utilizó 100.000) y no siempre la diferencia fue a favor del hilo ganador.

Pareciera que la prioridad modifica el tiempo que se asigna a la ráfaga de ejecución pero la lógica de los semáforos es invulnerable a esta prioridad.

## **Ejercicio 3. El poder del paralelismo**
### Inciso 1.
### proyectosor1ungstula/enunciado2/ejercicio3/

La implementación con paralelismo de datos es : *paralelismoDatos.c*

La versión secuencial de la misma es: *paralelismoDeDatosNOsecuencial.c*

La implementación con paralelismo de tareas es : *paralelismoTarea.c*

La versión secuencial de la misma es: *paralelismoDeTareaNOsecuencia.c*


La versión con paralelismo de tareas tiene un promedio de 0,015s de ejecución. Con picos máximos de 0,023s y mínimos de 0,005s

La versión secuencial de paralelismo de tareas tiene un promedio de 0,005s

:-(



