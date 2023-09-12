
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void bart() {
    write(1, "Bart\n", 5);
    sleep(1);
}

void lisa() {
    write(1, "Lisa\n", 5);
    sleep(1);
}

void maggie() {
    write(1, "Maggie\n", 7);
    sleep(1);
}

void homer() {
    write(1, "Homer\n", 6);
    sleep(1);

    pid_t pid_bart = fork();
    if(pid_bart == 0) {
        bart();
    } else {
        pid_t pid_lisa = fork();
        if(pid_lisa == 0) {
            lisa();
        } else {
            pid_t pid_maggie = fork();
            if(pid_maggie == 0) {
                maggie();
            }
        }
    }    
}

void abraham() {
    write(1, "Abraham\n",8);
    sleep(1);
}

int main(int argc, char const *argv[]) {
    pid_t pid = fork();
    if(pid == -1) exit(EXIT_FAILURE);
    else if(pid == 0){
        homer();
    } else {
        abraham();
    }
    exit(EXIT_SUCCESS); // cada uno finaliza su proceso
}
