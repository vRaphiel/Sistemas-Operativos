/*
 * - Corre sobre 8 nucleos y calcula promedios por fila de un archivo de entrada de una matriz de NxM.
 * - El promedio de cada fila es calculado por un proceso separado. Máximo de 8 procesos simultáneos.
 * - Comunicación por pipes
 * - Cada proceso recibe por separado una fila para calcular.
 * - El proceso padre lo distribuye con round-robin
 * - La salida del programa es salida estandar.
*/

int cargar_fila(const int fd, int* lista) {}
int calcular_promedio(const int *lista) {}
void sort(char *s) {}
int dup2( int oldfd, int newfd) {}

pid_t procesos[8];
int pipes_hijo_padre[8][2];
int pipes_padre_hijo[8][2];

void hijo(int proceso, int pipes_padre_hijo[8][2], int pipes_hijo_padre[8][2]) {
    for(int i = 0; i < 8; i++) {
        if(i != proceso) {
            close(pipes_padre_hijo[i][0]);
            close(pipes_padre_hijo[i][1]);
            close(pipes_hijo_padre[i][0]);
            close(pipes_hijo_padre[i][1]);
        } else {
            close(pipes_padre_hijo[i][1]);
            close(pipes_hijo_padre[i][0]);
        }
    }

    int *filas;

    if(read(pipes_padre_hijo, filas) == -1) {
        exit(-1);
    }

    int *result;
    if(cargar_fila(fila, result) == 0){
        exit(-1);
    }
    int promedio = calcular_promedio(result);
    if(write(pipes_hijo_padre[proceso], promedio) == 0){
        exit(-1);
    }
}

int main(int argc, char const *argv[]) {
    int cantidad_tratada = 0;
    int matriz[10][10];

    if(sizeof(matriz) > 8) {
        cantidad_tratada = 8;
    } else {
        cantidad_tratada = sizeof(matriz);
    }

    for(int i = 0; i < cantidad_tratada; i++) {
        pid_t proceso = fork();
        procesos[i] = proceso;
        if(proceso == 0) {
            hijo(i, pipes_padre_hijo, pipes_hijo_padre);
        }
    }

    for(int i = 0; i < 8; i++) {
        close(pipes_hijo_padre[i][0]);
        close(pipes_hijo_padre[i][1]);
    }

    int valor = 0;
    while(valor < sizeof(matriz)) {
        int proceso = valor % 8;
        if(write(pipes_padre_hijo[proceso], valor) == -1){
            exit(-1);
        }
    }
    
    for(int i = 0; i < 8; i++) {
        close(pipes_padre_hijo[i][0])
        close(pipes_padre_hijo[i][1])
    }
    
    return 0;
}
