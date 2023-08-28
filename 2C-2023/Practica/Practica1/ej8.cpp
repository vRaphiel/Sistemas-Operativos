#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int dato = 0;
    pid_t pid = fork();
    // Si no hy error, pid vale 0 para el hijo y el valor del process id del hijo para el padre
    if(pid == -1) exit(EXIT_FAILURE);
    else if(pid == 0) {
        for(int i = 0; i < 3; i++) {
            dato++;
            printf("Dato hijo: %d\n", dato);
        }
    } else {
        for(int i = 0; i < 3; i++) {
            printf("Dato padre: %d\n", dato);
        }
    }
    exit(EXIT_SUCCESS);
}
