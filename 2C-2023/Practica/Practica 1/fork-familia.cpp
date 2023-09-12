#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void jennifer() {
	//hijo - Jennifer 
	write(1, "Soy Jennifer\n", 14);
	sleep(1);
}

void julieta() {
	//hijo Julieta 
	write(1,"Soy Julieta\n", 12);
  	pid_t pid = fork();
	//si es -1, hubo un error
    if (pid == -1) {
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		jennifer();
	}
}

void jorge() {
	write(1, "Soy Jorge\n", 10);
	sleep(1);	
}

void juan() {
	write(1, "Soy Juan\n", 10);
	sleep(1);						
	// Creo a Jorge
  	pid_t pid = fork();
	//si es -1, hubo un error
    if (pid == -1){
		exit(EXIT_FAILURE);  
	} else if(pid == 0) { 
		jorge();					
	}	
}

int main(int argc, char const *argv[]){
  pid_t pid = fork();
  //si no hay error, pid vale 0 para el hijo
  //y el valor del process id del hijo para el padre
  if (pid == -1) exit(EXIT_FAILURE);  
  //si es -1, hubo un error
  else if (pid == 0) {
	julieta();
  } else {
	juan();
  }
  exit(EXIT_SUCCESS); //cada uno finaliza su proceso
}
