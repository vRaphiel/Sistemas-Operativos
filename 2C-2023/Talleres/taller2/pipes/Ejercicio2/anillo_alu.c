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

void handler_anillo(int sig) {
	exit(EXIT_SUCCESS);
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
	int pipes[n][2];
	if (pipe(npipe) == -1) {
		perror("pipe");
		exit(1);
	}
	for(int i = 0; i < n; i++) {
		if(pipe(pipes[i]) == -1) {
			perror("pipe");
			exit(1);
		}
	}

	int esIgualOMayor = 0;
	int iteraciones = 0;

	pid_t procesos[n];

	printf("Procedo a crear los procesos\n");

	for(int i = 0; i < n; i++) {
		pid_t pid = fork();
		procesos[i] = pid;
		if(pid == 0) {
			signal(SIGTERM, handler_anillo);
			// Estoy en el hijo - Entonces cierro pipes innecesarios
			int prev = 0;
			if(i == 0) {
				prev = n-1;
			} else {
				prev = i-1;
			}
			if(i != start) {
				close(npipe[0]);
				close(npipe[1]);
			}
			if(i == 0) {
				// Cierro la escritura en pipe n-1 pero leo de el
				close(pipes[n-1][1]);
				dup2(pipes[n-1][0], STDIN_FILENO);
				// Cierro la lectura del pipe 0 pero escribo en el
				close(pipes[0][0]);
				dup2(pipes[0][1], STDOUT_FILENO);
				// Cierro los pipes del 1 al n-2 porque no los necesito
				for(int j = 1; j < n-1; j++) {
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
			} else if (i == n-1) { // Soy el pipe n - 1
				// Cierro la escritura en el pipe n-2 pero leo de el
				close(pipes[n-2][1]);
				dup2(pipes[n-2][0], STDIN_FILENO);
				// Cierro la lectura del pipe 0 pero escribo en el
				close(pipes[n-1][0]);
				dup2(pipes[n-1][1], STDOUT_FILENO);
				for(int j = 0; j < n-2; j++) {
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
			} else {
				for(int j = 0; j < n; j++) {
					if( j == i || j == prev) {
						if(j == i) { // Soy el proceso i, quiero leer del pipe i-1
							close(pipes[j][0]);
							dup2(pipes[j][1], STDOUT_FILENO);
						} else { // j == i - 1
							close(pipes[prev][1]);
							dup2(pipes[prev][0], STDIN_FILENO);
						}
					} else {
						close(pipes[j][0]);
						close(pipes[j][1]);
					}
				}
			}

			while(esIgualOMayor == 0) {

				int random = 0;
				if(i == start && iteraciones == 0) {
					int mensaje = 0;
					random = generate_random_number();
					iteraciones++;
					if(read(npipe[0], &mensaje, sizeof(int)) == -1) {
						perror("pipe read from parent");
						exit(1);
					}
					if(write(pipes[i][1], &mensaje, sizeof(int)) == -1) {
						perror("pipe write to next and start sequence");
						exit(1);
					}
				}

				if(i == start && iteraciones > 0){
					int resultado = 0;
					if(read(pipes[prev][0], &resultado, sizeof(int)) == -1) {
						perror("pipe read from prev to check ring");
						exit(1);
					}
					if(resultado > random){
						esIgualOMayor == 1;
						if(write(npipe[1], &resultado, sizeof(int)) == -1) {
							perror("pipe write to parent");
							exit(1);
						}
						exit(0);
					} else {
						resultado++;
						if (write(pipes[i][1], &resultado, sizeof(int)) == -1) {
							perror("pipe write continue ring");
							exit(1);
						}
					}
				}

				if(i != start) {
					int number = 0;
					if(read(pipes[prev][0], &number, sizeof(int)) == -1) { 
						printf("pipe current is %d", i);
						exit(1); 
					}
					printf("Current value is %d", number);
					number++;
					if(write(pipes[i][1], &number, sizeof(int)) == -1) {
						perror("pipe write to next");
						printf("pipe number %d\n", i);
						exit(1);
					}
				}
			}
		} else {
			for(int j = 0; j < n; j++) {
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
		}
	}
	int resultado_final = 0;
	while(read(npipe[0], &resultado_final, sizeof(int)) != 0) {}
	for(int i = 0; i < n; i++) {
		kill(procesos[i], SIGTERM);
	}
	printf("Terminamos con la ejecución con valor %d", resultado_final);
}
