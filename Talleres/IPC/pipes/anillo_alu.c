#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{	
	int status, pid, n, s;
	int buffer[1];
	int npipe[2];

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
	fprintf(stderr, "Uso: %s, con n = %s, c = %s y s = %s\n", argv[0], argv[1], argv[2], argv[3]);
	
	sscanf (argv[1],"%i",&n);
	sscanf (argv[2],"%i",&buffer[0]);
	sscanf (argv[3],"%i",&s);

	printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer[0], s);

	pid_t procesos[n];
		if (pipe(npipe) == -1) {
		perror("pipe");
		exit(1);
	}

	// Estoy en el padre
	if (write(npipe[1], &buffer[0], sizeof(int)) != sizeof(int)) {
		perror("Escritura");
		exit(1);
	}

	int is_equals = 0;
	int iteraciones = 0;
	int a = s;

	//Creo el pipe que va a mandar el mensaje siempre

	while(is_equals == 0){
		
		pid_t pid_h = fork();
		procesos[a] = pid_h;
		
		if(pid_h == 0){
			// La primera vez
			if(a == s && iteraciones == 0){
				int r = (rand() % (buffer[0]*5 - (buffer[0] + 1)) + (buffer[0] + 1));
				if (write(npipe[1], &r, sizeof(int)) != sizeof(int)) {
					perror("Escritura");
					exit(1);
				}
			}

			if(a == s && iteraciones > 0){
				// Aca tengo que checkear el valor. 
				int resultado = 0;
				if (read(npipe[0], &resultado, sizeof(int)) > 0){}

				if(buffer[0] > resultado){
					is_equals == 1;
					exit(0);
				} else {
					if (write(npipe[1], &resultado, sizeof(int)) != sizeof(int)) {
						perror("Escritura");
						exit(1);
					}
				}
			}

			printf("Hola mundo, el valor del buffer actual es es %i", buffer[0]);

			buffer[0] = buffer[0] + 1;

			close(npipe[0]);
			close(npipe[1]);
		}
		if(a == n-1){
			a = 0;
		} else {
			a++;
		}
	}

	printf("Hola mundo, el resultado es %i", buffer[0]);

}