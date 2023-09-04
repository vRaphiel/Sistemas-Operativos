#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"

int generate_random_number() {
	return (rand() % 50);
}

int main(int argc, char **argv) {	
	//Funcion para cargar nueva semilla para el numero aleatorio
	srand(time(NULL));

	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}

  	/* COMPLETAR */
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);
	
	int npipe[2];
	pid_t procesos[n];
	if (pipe(npipe) == -1) {
		perror("pipe");
		exit(1);
	}

	// Estoy en el padre
	if (write(npipe[1], &buffer, sizeof(int)) != sizeof(int)) {
		perror("Escritura");
		exit(1);
	}

	int is_equals = 0;
	int iteraciones = 0;
	int a = start;

	//Creo el pipe que va a mandar el mensaje siempre

	while(is_equals == 0){
		
		pid_t pid_h = fork();
		procesos[a] = pid_h;
		
		if(pid_h == 0){
			// La primera vez
			if(a == start && iteraciones == 0){
				int r = generate_random_number();
				if (write(npipe[1], &r, sizeof(int)) != sizeof(int)) {
					perror("Escritura");
					exit(1);
				}
			}

			if(a == start && iteraciones > 0){
				// Aca tengo que checkear el valor. 
				int resultado = 0;
				if (read(npipe[0], &resultado, sizeof(int)) > 0){}

				if(buffer > resultado){
					is_equals == 1;
					exit(0);
				} else {
					if (write(npipe[1], &resultado, sizeof(int)) != sizeof(int)) {
						perror("Escritura");
						exit(1);
					}
				}
			}

			printf("Hola mundo, el valor del buffer actual es es %i", buffer);

			buffer = buffer + 1;

			close(npipe[0]);
			close(npipe[1]);
		}
		if(a == n-1){
			a = 0;
		} else {
			a++;
		}
	}

	printf("Hola mundo, el resultado es %i", buffer);
    
}
