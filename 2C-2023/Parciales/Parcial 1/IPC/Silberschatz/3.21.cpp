#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void handler_hijo(int sig){    
    printf("Terminamos el proceso\n");
    exit(EXIT_FAILURE);
}

int child_method(int pipes[2][2]) { 
    signal(SIGTERM, handler_hijo);
    close(pipes[0][1]);
    close(pipes[1][0]);
    int numero;
    if(read(pipes[0][0], &numero, sizeof(int)) == -1) {
        perror("pipe read from parent");
        exit(1);
    }

    while(numero > 1) {
        if((numero % 2) == 0){
            numero = (numero / 2);
        } else {
            numero = (3*numero) + 1;
        }
        if(write(pipes[1][1], &numero, sizeof(int)) == -1) {{
            perror("pipe write to parent");
            exit(1);
        }}
    }

    if(write(pipes[1][1], &numero, sizeof(int)) == -1) {{
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
    int pipes[2][2];

    for(int i = 0; i < 2; i++){
        pipe(pipes[i]);
    }

    pid_t child = fork();
    if(child == 0) {
        child_method(pipes);
    } else {
        close(pipes[0][0]);
        close(pipes[1][1]);
        int numero = 8;
        if(write(pipes[0][1], &numero, sizeof(int)) == -1) {
            printf("Error");
            exit(-1);
        }

        int valor;
        printf("valor %d\n", numero);
        int read_status = -1;
        while ((read_status = read(pipes[1][0], &valor, sizeof(int))) != 0) {
            if (read_status == -1) {
                perror("read pipes_padre_a_hijo");
            } else {
                printf("valor %d\n", valor);
            }
        }

        printf("Finished");
    }
    return 0;
}
