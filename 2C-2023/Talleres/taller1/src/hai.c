#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int contador = 0;
int continuo = 0;

void handler_child(int sig) {
	printf("Ya va!\n");
	contador = contador + 1;
	return;
}

void hijo() {
	signal(SIGURG, handler_child);
	while(contador < 5) {}
	continuo = 1;
	pid_t ppid = getppid();
	kill(ppid, SIGINT);
}

void handler_int(int sig) {
	wait(NULL);
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
	pid_t pid = fork();
	signal(SIGINT, handler_int);

	if(pid == 0) {
		hijo();
		while(continuo == 0) {}
		execvp(argv[1], argv+1);
	} else {
		for(int i = 0; i < 6; i++) {
			sleep(1);
			write(1, "sup!\n", 5);
			kill(pid, SIGURG);
		}
		sleep(1);
	}
	return 0;
}
