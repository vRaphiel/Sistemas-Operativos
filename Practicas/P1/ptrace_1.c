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
{   
    int child;
    int status;
     long orig_rax;
    child = fork();

    if(child == 0)
    {
        // Indico que quiero que me traceen
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        kill(getpid(), SIGSTOP);

        // Llamo a una inocente syscall
        write(0, "SO!\n", 4);

        exit(0);
    }
    else 
    {     
            // Alternativa, empezar con el padre. Pero ojo!
            //ptrace(PTRACE_ATTACH,child, 0, 0);
        	
            // Espero a recibir un evento del hijo. Salgo si terminó con errores
            if(wait(&status) < 0){perror("wait");return 0;}

            // Si termino "normalmente" (no recibió señal) también salgo
            if(WIFEXITED(status)) return 0;

            orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX,NULL);
            printf("System call del hijo: %ld\n", orig_rax);

            ptrace(PTRACE_SYSCALL, child, 0, 0);

            if(wait(&status) < 0){perror("wait");return 0;}

            if(WIFEXITED(status)) return 0;

            orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX,NULL);
            printf("System call del hijo: %ld\n", orig_rax);

            // "Soltamos" al hijo antes de terminar
            ptrace(PTRACE_DETACH, child, 0, 0);
     
    }
    return 0;
}
