#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void handler_hijo(int sig){    
    printf("Terminamos el proceso\n");
    exit(EXIT_FAILURE);
}

int child_method(int numero) { 
    signal(SIGTERM, handler_hijo);
    printf("valor %d\n", numero);
    while(numero > 1) {
        if((numero % 2) == 0){
            numero = (numero / 2);
        } else {
            numero = (3*numero) + 1;
        }
        printf("valor %d\n", numero);
    }
    exit(1);
}

int main(int argc, char const *argv[]) {
    pid_t child = fork();
    if(child == 0) {
        int numero = 8;
        child_method(numero);
    }
    wait(NULL);
    printf("Finished on parent");
    return 0;
}
