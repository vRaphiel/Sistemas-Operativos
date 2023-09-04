#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int n;
int numero_maldito;
int hijosCreados = 0;
pid_t hijos[10];

int generate_random_number(){
	return (rand() % n);
}

void handler_hijo(int sig){
    int rNum = generate_random_number();
    if(numero_maldito == rNum) {
        printf("Coincidimos. Caemos en el abismo\n");
        exit(EXIT_FAILURE);
    }
}

void hijo() {
	signal(SIGTERM, handler_hijo);
    printf("Hijo creado\n");
    while(1) {
    }
}

void sig_children(int sig) {
    pid_t pid = wait(NULL);
    for(int j = 0; j < n; j++) {
        if(pid == hijos[j]) {
            hijos[j] = 0;
        }
    }
    return;
}

int main(int argc, char const *argv[]){
    //Funcion para cargar nueva semilla para el numero aleatorio
    srand(time(NULL));
    
    signal(SIGCHLD, sig_children);
    
    n = atoi(argv[1]);
	int rondas = atoi(argv[2]);
	numero_maldito = atoi(argv[3]); 
    
    for(int i = 0; i < n; i++) {
        pid_t pid = fork();
        hijos[i] = pid;
        if(pid == 0) {
            hijo();
        }
    }

    printf("Todos los hijos han sido creados\n");

    for(int i = 0; i < rondas; i++) {
        for(int j = 0; j < n; j++) {
            kill(hijos[j], SIGTERM);
            sleep(1);
        }
        printf("Terminó esta iteración\n");
    }

    printf("Terminó la secuencia. Procedemos a deshacernos de los restantes\n");

    for(int j = 0; j < n; j++) {
        if(hijos[j] != 0){
            printf("Muere el hijo %d\n", j);
            kill(hijos[j], SIGKILL);
        }
    }

    printf("Hola");

    exit(0);
}