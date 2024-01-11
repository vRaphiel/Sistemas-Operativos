#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

void calcular(int *valor){}

void ejecutarHijo(int i, int pipes[][2]){
    /**
     * Crear un subproceso
     * Avisa al padre cuando terminó mediante una señal comunicando el resultado
     * El hijo sabiendo que terminó, tesponde al polling del padre enviandole el número y el resultado
    */
    int valor = 0;
    int pipefd1[2];
    int pipefd2[2];
    if(pipe(pipefd1) == 1){
        perror("Problema");
    }
    if(pipe(pipefd2) == 1){
        perror("Problema");
    }

    int numero;
    if(read(pipes[i][0], &numero, sizeof(numero)) == -1) {
        perror("Problema");
        exit(EXIT_FAILURE);
    }
    if(write(pipefd1[1], &numero, sizeof(numero)) == -1) {
        perror("Problema");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if(pid == 0) {
        int value;
        if(read(pipefd1[0], &value, sizeof(value)) == -1){
            perror("Problema");
        }
        calcular(&value);
        if(write(pipefd2[1], &value, sizeof(value)) == -1){
            perror("Problema");
        }
    } else {
        int resultado;
        if(read(pipefd2[0], &resultado, sizeof(resultado)) == -1){
            perror("Problema");
        }
        if(write(pipes[i][1], &numero, sizeof(numero)) == -1) {
            perror("Problema");
            exit(EXIT_FAILURE);
        }
        if(write(pipes[i][1], &resultado, sizeof(resultado)) == -1) {
            perror("Problema");
            exit(EXIT_FAILURE);
        }
    }
}