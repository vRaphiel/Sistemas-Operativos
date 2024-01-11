/**
 * Operación computacional que desea repartir entre N subprocesos.
 * Para ello el padre dispone de un método que dado un PID devolverá un número secreto
 * El número secreto deberá ser enviado al hijo correspondiente con pipes
 * 
 * Cada proceso debe encargarse de realizar el número correspondiente utilizando la función calcular.
 *      El número a usar es el que el padre le envió
 * 
 * Los subprocesos ejecutarán calcular y a medida que terminen informarán al padre
 * El padre debe llamar a la función informarResultado
 * 
 * La función informarResultado debe ser llama en el mismo orden en que fueron terminando su computo
*/

void ejecutarHijo(int i, int pipes[][2]) {

}

int main(int argc, char* argv[]){
    if(argc < 2) {
        printf("Debe ejecutar con la cantidad de hijos como parametro\n");
        return 0;
    }
    int N = atoi(argv[1]);
    int pipes[N*2][2];
    for(int i = 0; i < N*2; i++){
        pipe(pipes[i]);
    }
    for(int i = 0; i < N; i++){
        int pid = fork();
        if(pid == 0) {
            ejecutarHijo(i, pipes);
            return 0;
        } else {
            int numero = dameNumero(pid);
            write(pipes[i][1], &numero, sizeof(numero)); 
        }
    }
    int cantidadTerminados = 0;
    char hijoTermino[N] = {0};
    while(cantidadTerminados < N) {
        for(int i = 0; i < N; i++) {
            if(hijoTermino[i]) {
                continue;
            }
            char termino = 0;
            write(pipes[i][1], &termino, sizeof(termino));
            read(pipes[N+i][0], &termino, sizeof(termino));
            if(termino) {
                int numero;
                int resultado;
                read(pipes[N+i][0], &numero, sizeof(numero));
                read(pipes[N+i][0], &resultado, sizeof(resultado));
                informarResultado(numero, resultado);
                hijoTermino[i] = 1;
                cantidadTerminados++;
            }
        }
    }
    wait(NULL);
    return 0;
}