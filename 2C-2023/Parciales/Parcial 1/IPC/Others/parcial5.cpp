#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

bool hayNumero(){
    return true;
}
int leerNumero(){
    return 0;
}
bool esPerfecto(int numero) {
    return true;
}

int open(char* archivo, char data) {

}

void hijo(int pipes_desde_padre[][2], int pipes_desde_hijo[][2], int n, int pos) {
    // Cierro la escritura desde los padres, solo me interesa la lectura
    // Cierro la lectura desde los hijos, solo me interesa la escritura
    // Cierro todo menos el que voy a usar porque a un proceso no le interesa leer lo que reciben otros procesos
    for(int i = 0; i < n; i++){
        if(i != pos) {
            close(pipes_desde_padre[i][1]);
            close(pipes_desde_padre[i][0]);
            close(pipes_desde_hijo[i][0]);
            close(pipes_desde_hijo[i][1]);
        } else {
            close(pipes_desde_padre[i][0]);
            close(pipes_desde_hijo[i][1]);
        }
    }

    int numero;
    // Mientras se pueda leer
    while(read(pipes_desde_padre[pos][0], &numero, sizeof(numero)) != -1){
        if(esPerfecto(numero)) {
            if(write(pipes_desde_hijo[pos][1], &numero, sizeof(numero)) == -1) {
                perror("error writing pipe to parent");
                exit(EXIT_FAILURE);
            }
        }
    }
    // Como se que terminó entonces cierro lo necesario
    close(pipes_desde_padre[pos][1]);
    close(pipes_desde_hijo[pos][1]);
    exit(EXIT_SUCCESS);
}

int main(int argc, char const* argv[]) {
    int n = atoi(argv[1]);
    // COMPLETAR
    // n procesos
    pid_t procesos[n];
    int pipes_desde_padre[n][2];
    int pipes_desde_hijo[n][2];

    for(int i = 0; i < n; i++) {
        pipe(pipes_desde_padre[i]);
        pipe(pipes_desde_hijo[i]);
    }

    for(int i = 0; i < n; i++) {
        pid_t pid = fork();
        procesos[i] = pid;
        if(pid == 0) {
            hijo(pipes_desde_padre, pipes_desde_padre, n, i);
        }
    }

    for(int i = 0; i < n; i++) {
        close(pipes_desde_padre[i][0]);
        close(pipes_desde_hijo[i][1]);
    }

    int pos = 0;
    while(hayNumero()) {
        int siguienteNumero = leerNumero();
        if(write(pipes_desde_padre[pos][1], &siguienteNumero, sizeof(siguienteNumero)) == -1){
            perror("error writing from father");
        }
        // COMPLETAR
        if(pos == n-1) {
            pos = 0;
        } else {
            pos++;
        }
    }

    int totales[n];
    for(int i = 0; i < n; i++) {
        if(read(pipes_desde_hijo[i][0], &totales[i], sizeof(totales[i])) == -1) {
            perror("Error de escritura");
        }
        close(pipes_desde_padre[i][1]);
        close(pipes_desde_hijo[i][0]);
    }

    for (int i = 0; i < n; ++i) {
        int status;
        waitpid(procesos[i], &status, 0);
    }

    //--------------- AGREGADO EXTRA ----------------------
    int pipe_gpt[2];
    if(pipe(pipe_gpt) == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    // Defino que el pipe suelta por salida externa y recibe por salida externa
    dup2(pipe_gpt[0], STDIN_FILENO);
    dup2(pipe_gpt[1], STDOUT_FILENO);
    char *text;

    for(int i = 0; i < n; i++) {
        if(write(pipe_gpt[1], &totales[i], sizeof(totales[i])) == -1) {
            perror("error writing to startgpt");
        }
    }

    pid_t gpt = fork();
    if(gpt == 0) {
        //execve("startgpt", ["-generar-parrafo"]);
    }

    int status;
    waitpid(gpt, &status, 0);
    
    char texto = 'informe.txt';
    int pointer;
    if(pointer = open(&texto, 'O_APPEND') == -1){
        perror("Problema de escritura");
    }
    
    if(read(pipe_gpt[0], &text, sizeof(char)) == -1) {
        perror("error reading from startgpt");
    }

    if(dprintf(pointer, text) == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    exit(0);


    // COMPLETAR
}