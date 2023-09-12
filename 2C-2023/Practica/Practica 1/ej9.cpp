#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t pid = fork();
    if(pid == -1) exit(EXIT_FAILURE);
    else if(pid == 0) {
        write(1, "Soy Julieta\n", 12);
        sleep(1);
        pid_t pid_c = fork();
        if(pid_c == 0) {
            write(1, "Soy Jennifer\n\0", 14);
            sleep(1);
        }
    } else {
        write(1, "Soy Juan\n\0", 10);
        sleep(1);
        wait(NULL);
        pid_t pid_j = fork();
        if(pid_j == 0) {
            write(1, "Soy Jorge\n", 10);
            sleep(1);
        }
    }
    exit(EXIT_SUCCESS);
}
