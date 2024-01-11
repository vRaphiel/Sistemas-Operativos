#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <algorithm>
using namespace std;

void handler_hijo(int sig){    
    printf("Terminamos el proceso\n");
    exit(EXIT_FAILURE);
}

int child_method(int pipes[2][2]) { 
    signal(SIGTERM, handler_hijo);
    close(pipes[0][1]);
    close(pipes[1][0]);

    string palabra;
    if(read(pipes[0][0], &palabra, sizeof(palabra)) == -1) {
        perror("pipe read from parent");
        exit(1);
    }

    int pos = 0;
    int init = 0;
    while(pos < palabra.length()) {

        if((int) palabra[pos] == 32) {
            init == 0;
        } else {
            init++;
        }

        if(init > 0) {
            palabra[pos] = toupper(palabra[pos]);
        }
        pos++;
    }


    if(write(pipes[1][1], &palabra, sizeof(palabra)) == -1) {{
        perror("pipe write to parent");
        exit(1);
    }}

    close(pipes[0][0]);
    close(pipes[1][1]);
    exit(1);
}

int main(int argc, char const *argv[]) {
    // Pos 0 = Padre | Pos 1 = Hijo
    // PIPE_READ = 0
    // PIPE_WRITE = 1

    string entrada = argv[1];

    int pos = 0;
    int init = 0;
    while(pos < entrada.length()) {

        printf("%c\n", entrada[pos]);
        pos++;
    }



/*     int pipes[2][2];

    for(int i = 0; i < 2; i++){
        pipe(pipes[i]);
    }

    pid_t child = fork();
    if(child == 0) {
        child_method(pipes);
    } else {
        close(pipes[0][0]);
        close(pipes[1][1]);

        if(write(pipes[0][1], &entrada, sizeof(entrada)) == -1) {
            printf("Error");
            exit(-1);
        }
        string salida;
        int read_status = -1;
        if(read(pipes[1][0], &salida, sizeof(salida)) == -1) {
            perror("read pipes_padre_a_hijo");
        }
        printf("Inicial: %s \n", entrada);
        printf("Resultado: %s \n", salida);
        printf("Finished");
    } */
    return 0;
}
