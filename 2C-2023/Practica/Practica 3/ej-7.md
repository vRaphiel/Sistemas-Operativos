Se tienen N procesos de P_0 hasta P_N-1
Se requiere sincronizarlos de manera tal que la ejecución sea P_i, P_i+1,...,P_n-1, P_0,...,P_i-1
Escribir el código que deben ejecutar cada uno de los procesos para cumplir con la sincronización requeriza usando semáforos.

- Se recibe un valor "n" que indica la cantidad de procesos
- Se recibe un valor "i" que indica el inicio del proceso
- Los procesos se ejecutan en orden a partir del proceso "i". Entonces, desde 1...i-1 no se ejecutará nada si el proceso n no se ha ejecutado.
- Los procesos i+1...n no se ejecutarán hasta que el proceso i no se haya ejecutado

- Definimos una arreglo de semaforos
semaforos[n] = [sem(0)]
semaforos[i] = sem(1)

proceso(int i) {
    semaforos[i].wait()
    hacer()
    if(i == n -1){
        semaforos[0].signal()
    } else {
        semaforos[i+1].signal()
    }
}