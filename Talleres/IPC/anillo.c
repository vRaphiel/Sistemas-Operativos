#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){

	int fd[2];
	int leer;
	int escribir;
	int estatus;
	pid_t pid;
	int i = 1;
	int N, t[1];

	/* Parsing de los argumentos
	- Numero de procesos en el anillo <N>
	- numero a enviar <c>*/
	if (argc != 3)
	{
		printf("Uso: anillo <N> <c> \n");
		exit(0);
	}
	 
	N = atoi(argv[1]);
	t[0] = atoi(argv[2]);
	printf("Se crearán %i procesos y se enviarán el número %i\n", N, t[0]);
	   
	/* Se crea el pipe de entrada al proceso 1 */
	if (pipe(fd) < 0) {
		perror("Error al crear el pipe\n");
		exit(0);
	}
	leer= fd[0]; /* guardo el fd para leer en cada hijo */
	escribir = fd[1];
	write(escribir, t, 1);  /* se escribe el testigo en el primer pipe */    
	
	/* creo N procesos hijo */
	for(i = 0; i < N; i++) {
		if (i != N-1)
			if (pipe(fd) < 0) {
				perror("Error al crear el pipe\n");
				exit(0);
			}
		pid = fork();
		switch(pid) {
			case -1: /* error */
				perror("Error en el fork \n");
				exit(0);
                
			case 0: /* proceso hijo */
				if (i != N-1) {
					close(escribir);
					read(leer, t, 1); /* leo del pipe del antecesor */
					close(leer);
					printf("Soy el proceso %d, con testigo %d\n", i, t[0]);
					t[0]++; /* incremento testigo */
					close(fd[0]); /* cierro la lectura en mi propio pipe */
					write(fd[1], t, 1); /* escribo */
					close(fd[1]); /* cierro mi escritura */
				}
				break;
			default:
				if (i == N-1) { /* último proceso */
					read(leer, t, 1);
					close(leer); /* se destruye el pipe anterior */
					close(escribir); /* """ */
					printf("Soy el ultimo %d, con testigo %d\n", i, t[0]);
					exit(0);
				}
				else { /* proceso padre */
					if ((pid2 = waitpid(pid, &estatus, 0)) == -1)
						perror("wait() error");
					else {
						close(leer); /* se destruye el pipe anterior */
						close(escribir); /* """ */
						leer = fd[0]; /* reapunto leer al ultimo pipe creado */
						escribir = fd[1];
					}
				}
		}
		if (pid==0) /* para que salga el hijo del for  */
			break;
	}
	/* a continuación los procesos del anillo continuarían sus acciones */
	exit(0);
}
