// Ejercicio de juego de adivinanzas
int MAX_NUM = 50;

int pids = [10];
int pipes = [10][2];
int hijo = 0;
bool ganador = false;
int random = 0;

void main(){
    crearHijos();
    iniciarPipes();
    cerrarPipesParaPadre();
    random = Math.random(MAX_NUM);
    jugar();
}

void crearHijos(){
    for(hijo = 0; hijo < 10; hijo++){
        pid = fork();
        pids[hijo] = pid;
        if(pid == 0){
            ejecutarHijo();
        }
    }
}

void iniciarPipes(){
    for(int i = 0; i < 10; i++){
        pipe(pipes[i]);
    }
}

void handler(){
    ganador = 0;
}

void cerrarPipesParaPadre(){
    for(int i = 0; i < 10; i++){
        close(pipes[i][1]);
    }
}

void cerrarPipesParaHijo(){
    for(int i = 0; i < 10; i++){
        if(i != hijo){
            close(pipes[i][0]); 
            close(pipes[i][1]); 
        }
    }
    close(pipes[hijo][0]);
}

void ejecutarHijo(){
    signal(SIGTERM, handler);
    int num = Math.random(100);
    cerrarPipesParaHijo();
    while(!ganador){
        int pnum = Math.random(100);
        write(pipes[hijo][1], pnum, sizeof(pnum));
        sleep(1)
    }
    print("Gane");
    exit(0);
}

void jugar(){
    int vivos = 0;
    int i = 0;

    while(vivos > 1){
        if(pids[i]){
            int hnum;
            read(pipes[i][0], &hnum, sizeof(hnum));
            if (hnum > random)
            {
                printf("El loco la palmo");
                vivos--;
                kill(pids[i], SIGKILL);
                waitpid(pids[i], NULL, 0);
                pids[i] = 0;
            }
        }
        i = (i+1) % 10;
    }

    while(pids[i] == 0){
        i = (i+1) % 10;
    }

    print("El hijo ganador es %d", i);
    kill(pids[i], SIGTERM);
}


// ============================================================================================================================ //
/**
 * Un grupo de N estudiantes queire hacer un tp de su materia. Conocen implementarTp() y experimentar()
 * Cada etapa puede ser llevada independientemente. 
 * Para experimentar() todos deben haber terminado implementarTp()
*/
n, mutex = sem(1), barrera = sem(0);
implementarTp();

mutex.wait();
n = n + 1;
mutex.signal();

if(n < N){
    barrera.wait();
}

barrera.signal();
experimentar();

// ============================================================================================================================ //
/**
 * El acuerdo es que alguien puede empezar una nueva si todos terminaron la anterior ¿Podemos reutilizar la solución anterior?
 */

implementarTp()

mutex.wait()
n = n + 1
if(n == N)
    barrera.signal()
mutex.signal()
barrera.wait()
barrera.signal()

experimentar();

// ============================================================================================================================ //
/**
 * Modelar con semaforos un micro de larga distancia directo entre Bs As y Mendoza. Este tiene asiento para N personas y funciona como:
 * Empieza en Buenos Aires
 * Espera a llenarse
 * Viaja hasta Mendoza
 * Estaciona en una terminal, permitiendo que los pasajeros desciendan
 * Repite el procedimiento desde el principio pero desde la otra terminal
 */

permisoSubir = [sem(0), sem(0)]
asientos = sem(N)
asientosOcupados = sem(0)
permisoBajar = sem(0)

bus(ciudad)
    while(true){
        repeat N: permisoSubir[ciudad].signal()
        repeat N: asientosOcupados.wait()
        viajar(ciudad)
        repeat N: permisoSubir[ciudad].wait()
        repeat N: permisoBajar.signal()
        ciudad = 1 - ciudad
    }
}

pasajero(i, ciudad){
    permisoSubir[ciudad].wait()
    asientos.wait()
    subir(i, ciudad)
    asientoOcupado.signal()
    permisoBajar.wait()
    bajar(i, ciudad)
    asiento.signal()
}
