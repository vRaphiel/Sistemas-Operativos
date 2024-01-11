#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

int pipefd1[2], pipefd2[2];

void MANEJADOR(int signum) {
    printf("Alarma: el tiempo termino\n");
    exit(EXIT_SUCCESS);
    // TODO
}

void PIPES(void) {
    if(pipe(pipefd1) < 0 || pipe(pipefd2) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void HABLAR_AL_PADRE(void) {
    //TODO2
    int num = 1;
    if(write(pipefd2[1], &num, sizeof(int)) == -1) {
        perror("bad writing from children to parent");
    }
    printf("El hijo envia un mensaje al padre!\n");
}

void ESPERAR_AL_PADRE(void) {
    // TODO3
    int valor = 0;
    while(valor == 0) {
        if(read(pipefd1[0], &valor, sizeof(int)) == -1) {
            perror("");
        }
    }
    printf("El hijo recibe un mensaje desde el padre!\n");
}

void HABLAR_AL_HIJO(void) {
    // TODO4
    int num = 1;
    if(write(pipefd1[1], &num, sizeof(int)) == -1) {
        perror("bad waiting from parent to children");
    }
    printf("El padre envia un mensaje al hijo!\n");
}

void ESPERAR_AL_HIJO(void) {
    // TODO5
    int valor = 0;
    while(valor == 0) {
        if(read(pipefd2[0], &valor, sizeof(int)) == -1) {
            perror("bad reading in parent from children");
        }
    }
    printf("El padre recibe un mensaje desde el hijo!\n");
}

int main(int argc, char* argv[]) {
    PIPES();
    pid_t pid;
    pid = fork();

    signal(SIGALRM, MANEJADOR);
    alarm(10);

    if(pid != 0) {
        // SOY EL PADRE
        close(pipefd1[0]);
        close(pipefd2[1]);
        while(1) {
            sleep(rand()%2+1);
            HABLAR_AL_HIJO();
            ESPERAR_AL_HIJO();
        }
    } else {
        close(pipefd1[1]);
        close(pipefd2[0]);
        signal(SIGALRM, MANEJADOR);
        while(1) {
            sleep(rand()%2 + 1);
            ESPERAR_AL_PADRE();
            HABLAR_AL_PADRE();
        }
    }
    return 0;
}
