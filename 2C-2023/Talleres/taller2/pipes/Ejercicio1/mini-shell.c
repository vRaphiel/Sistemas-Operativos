#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"

void ejecutar_cmd(char* cmd, char* p) {
  execlp(cmd, cmd, p, NULL);
}

// 0 ES LECTURA - 1 ES ESCRITURA

void hijo(char ***progs, int pipes[][2], int position, int pipe_qty) {
	for(int i = 0; i < pipe_qty; i++) {
		if( position == 0 ) {
			if( position == i ) {
				close(pipes[i][0]);
				dup2(pipes[i][1], STDOUT_FILENO);
			}
		} else if( position == pipe_qty - 1) {
			if( position == i ) {
				close(pipes[i][1]);
				dup2(pipes[i][0], STDIN_FILENO);
			}
		} else {
			if( i == position || i == position - 1 ) {
				if(i != position) {
					close(pipes[i][0]);
					dup2(pipes[i][1], STDOUT_FILENO);
				} else {
					close(pipes[i][1]);
					dup2(pipes[i][0], STDIN_FILENO);
				}
			} else {
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
		}
	}
	execvp(progs[position][0], progs[position]);
	exit(0);
}

static int run(char ***progs, size_t count) {	
	int r, status;

	//Reservo memoria para el arreglo de pids
	//TODO: Guardar el PID de cada proceso hijo creado en children[i]
	pid_t *children = malloc(sizeof(*children) * count);
	int pipes[count - 1][2];

	for(int i = 0; i < count - 1; i++){
		int p = pipe(pipes[i]);
		if(p == -1) perror("Error");
	}

	//TODO: Pensar cuantos procesos necesito
	for(int i = 0; i < count; i++) {
		pid_t pid = fork();
		if(pid == 0) {
			hijo(progs, pipes, i, count - 1);
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
