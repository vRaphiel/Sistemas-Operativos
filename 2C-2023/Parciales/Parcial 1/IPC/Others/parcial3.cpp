#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

using namespace std;

void traducir(char* linea, char* linea_traducida){}

int hijo(int pipes_to_parent[][2], int pipes_from_parent[][2], int position) {
    char* linea;
    char* linea_traducida;

    if(read(pipes_from_parent[position][0], &linea, sizeof(linea)) == -1) {
        perror("Error de lectura de padre");
        exit(EXIT_FAILURE);
    }
    traducir(linea, linea_traducida);    

    if(write(pipes_to_parent[position][1], &linea_traducida, sizeof(linea_traducida)) == -1) {
        perror("Error de escritura a padre");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char const *argv[]) {
    return 0;
}
