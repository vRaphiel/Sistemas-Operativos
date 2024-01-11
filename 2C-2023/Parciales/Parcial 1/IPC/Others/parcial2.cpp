#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {

	int n = atoi(argv[1]);
	//string p = argv[1];

	if (argc != 2){ printf("Uso: anillo <p> <n> \n"); exit(0);}
    
    printf("Se crearán %i procesos \n", n);

    int pipes[n][0];
    int pipefd1[2];
    pid_t procesos[n];

    for(int i = 0; i < n; i++){
        if(pipe(pipes[i]) == -1) {
            perror("Error de pipes");
            exit(EXIT_FAILURE);
        }
    }

    if(pipe(pipefd1) == -1) {
        perror("Error de pipes");
        exit(EXIT_FAILURE);
    }

    string s = "telefono";
    //execve(p);
    
    if(write(pipefd1[1], &s, sizeof(s)) == -1) {
        printf("Error de pipe");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < n; i++) {
        pid_t pid = fork();
        if(pid == 0) {
            int prev = ((i+n-1) % n);
            for(int j = 0; j < n; j++) {
                if(j != i && j != prev) {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
                if(j == i) close(pipes[j][0]);
                if(j == prev) close(pipes[j][1]);
            }
            if(i != 0) {
                close(pipefd1[0]);
                close(pipefd1[1]);
            } else {
                close(pipefd1[1]);
            }

            if(i == 0){
                string cadena;
                if(read(pipefd1[0], &cadena, sizeof(cadena)) == -1){
                    perror("Error de pipe desde padre");
                    exit(EXIT_FAILURE);
                }
                char d = 's';
                cadena += d;
                printf("cadena es: %s \n", cadena.c_str());
                if(write(pipes[i][1], &cadena, sizeof(cadena)) == -1) {
                    perror("Error de pipe en escritura value 0");
                    exit(EXIT_FAILURE);
                }
                string cadenaFinal;
                if(read(pipes[prev][0], &cadenaFinal, sizeof(cadena)) == -1) {
                    perror("Error de pipe en lectura value 0");
                }
                close(pipes[prev][0]);
                close(pipes[i][1]);
                close(pipefd1[0]);
                close(pipefd1[1]);
                printf("original: %s\n", cadena.c_str());
                printf("final: %s\n", cadenaFinal.c_str());
            } else {
                string cadena;
                if(read(pipes[prev][0], &cadena, sizeof(cadena)) == -1){
                    perror("Error de pipe en escritura value other");
                    exit(EXIT_FAILURE);
                }
                printf("Current msg %s\n", cadena.c_str());
                char d = 's';
                cadena += d;
                if(write(pipes[i][1], &cadena, sizeof(cadena)) == -1) {
                    perror("Error de pipe en lectura value other");
                    exit(EXIT_FAILURE);
                }
                close(pipes[prev][0]);
                close(pipes[i][1]);
            }
        }
    }
    wait(NULL);
    return 0;
}
