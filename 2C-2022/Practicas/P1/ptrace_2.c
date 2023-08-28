#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/reg.h>   
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char* argv[])
{   int child;
    long orig_rax;
    long rax;
    int status;
    child = fork();
    if(child == 0) {

        ptrace(PTRACE_TRACEME, 0, 0, 0);
        kill(getpid(), SIGSTOP);

        for(int i = 0; i < 4; i++)
            write(0, "SO!\n", 4);

        exit(0);
    
    }
    else {
        while(1)
        {
        	// Si termino con errores
            if(wait(&status) < 0){perror("wait");break;}

            // Si termino "normalmente" (no recibió señal)
            if(WIFEXITED(status)) break;

            orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX,NULL);
            printf("System call del hijo:%ld\n", orig_rax);
        
			ptrace(PTRACE_SYSCALL, child, 0, 0);
        }
        ptrace(PTRACE_DETACH, child, 0, 0);
        
    }
    return 0;
}
