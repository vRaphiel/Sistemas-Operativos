#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"

void hijo(int pipe_fd_entrada[], int pipe_fd_salida[], int location, char ***progs, int command) {
	if(location == 0) {
		// Es entrada -> Cierro lectura
		close(pipe_fd_salida[0]);
		// Conectar escritura a stdout
		dup2(pipe_fd_salida[1], STDOUT_FILENO);
	} else if (location == 2) {
		// Es salida -> Cierro escritura
		close(pipe_fd_entrada[1]);
		// Conectar lectura a stdin
  		dup2(pipe_fd_entrada[0], STDIN_FILENO);
	} else {
		close(pipe_fd_salida[0]);
		close(pipe_fd_entrada[1]);
		dup2(pipe_fd_salida[1], STDOUT_FILENO);
		dup2(pipe_fd_entrada[0], STDIN_FILENO);
	}
	execvp(progs[command][0], progs[command]);
}

void hijo_aux(int pipes[][2], int location, char ***progs, int command, int size) {
	if(location == 0) {
		close(pipes[0][0]);
		dup2(pipes[0][1], STDOUT_FILENO);
		for(int i = 1; i < size; i++){
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
	} else if (location == 2) {
		// Es salida -> Cierro escritura
		close(pipes[size-1][1]);
		dup2(pipes[size-1][0], STDIN_FILENO);
		for(int i = 0; i < size-1; i++){
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
	} else {
		for(int i = 0; i < size-1; i++){
			if(i == command - 1) {

			}
			if(i == command + 1) {

			}
			close(pipes[i][0]);
			close(pipes[i][1]);
		dup2(pipes[i][1], STDOUT_FILENO);
		dup2(pipes[i-1][0], STDIN_FILENO);
		}

	}
	execvp(progs[command][0], progs[command]);
}

static int run(char ***progs, size_t count) {	
	int r, status;

	//Reservo memoria para el arreglo de pids
	//TODO: Guardar el PID de cada proceso hijo creado en children[i]
	pid_t *children = malloc(sizeof(*children) * count);

	int pipe_s = count - 1;
	int pipes[pipe_s][2];
	for(int i = 0; i < pipe_s; i++) {
		pipe(pipes[i]);
	}

	//TODO: Pensar cuantos procesos necesito
	for(int i = 0; i < count; i++) {
		pid_t pid = fork();
		children[i] = pid;
		if(pid == 0) {
			if(i == 0) {
				// Solo tengo que tener el pipe[0] con escritura. Todos los demás estan cerrados
				close(pipes[0][0]);
				for(int j = 1; j < pipe_s; j++) {
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
				dup2(pipes[0][1], STDOUT_FILENO);

				execvp(progs[i][0], progs[i]);
			} else if(i == pipe_s) {
				// Solo tengo que tener el pipe[n-1] con lectura. Todos los demás estan cerrados
				close(pipes[pipe_s-1][1]);
				for(int j = 0; j < pipe_s-1; j++) {
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
				dup2(pipes[pipe_s-1][0], STDIN_FILENO);
				execvp(progs[i][0], progs[i]);
			} else {
				// Tengo que ver el proceso en el que estoy. Si soy proceso 1 entonces necesito pipe 0 y pipe 1
				// ps0 pipe0 ps1 pipe1 ps2

				// Solo tengo que tener el pipe[n-1] con lectura. Todos los demás estan cerrados
				for(int j = 0; j < pipe_s; j++) {
					if(j == i - 1) {
						close(pipes[j][1]);
						dup2(pipes[j][0], STDIN_FILENO);
					} else if(j == i) {
						close(pipes[j][0]);
						dup2(pipes[j][1], STDOUT_FILENO);
					} else {
						close(pipes[j][0]);
						close(pipes[j][1]);
					}
				}
				execvp(progs[i][0], progs[i]);
			}
		}
	}
	//TODO: Pensar cuantos pipes necesito.

	//TODO: Para cada proceso hijo:
			//1. Redireccionar los file descriptors adecuados al proceso
			//2. Ejecutar el programa correspondiente

	//Espero a los hijos y verifico el estado que terminaron

	for (int i = 0; i < count; i++) {
		waitpid(children[i], &status, 0);

		if (!WIFEXITED(status)) {
			fprintf(stderr, "proceso %d no terminó correctamente [%d]: ",
			    (int)children[i], WIFSIGNALED(status));
			perror("");
			return -1;
		}
	}

	r = 0;
	free(children);

	return r;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("El programa recibe como parametro de entrada un string con la linea de comandos a ejecutar. \n"); 
		printf("Por ejemplo ./mini-shell 'ls -a | grep anillo'\n");
		return 0;
	}
	int programs_count;
	char*** programs_with_parameters = parse_input(argv, &programs_count);

	printf("status: %d\n", run(programs_with_parameters, programs_count));

	//fflush(stdout);
	//fflush(stderr);

	return 0;
}
