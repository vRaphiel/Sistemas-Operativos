#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int contador = 0;
int continuar = 1;

void signal_handler_p(){
	continuar = 0;
	return;
}

void signal_handler(){
	contador++;
	write(1,"Ya va!\n",7);
	return;
}

void hijo(){
	signal(SIGURG,signal_handler);
	while(contador < 4){}
	if(contador == 4){
		pid_t pid_p = getppid();
		kill(pid_p, SIGINT);
	}
}

int main(int argc, char* argv[]) {

	pid_t pid_h;
	pid_h = fork();
	if(pid_h == 0) {
		hijo();
	} else{
		signal(SIGINT, signal_handler_p);
		while(continuar == 1){
			// Ejecuto al hijo
			sleep(1);
			write(1,"Sup!\n>",5);
			kill(pid_h, SIGURG);
		}
	}
	
	return 0;
}
