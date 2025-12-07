### Signaling (Cuando thread A ocurre antes que B)
```
semaforo semaforo = sem(0)

procesoA():
    A1()
    semaforo.signal()
    A2()

procesoB():
    B1()
    semaforo.wait()
    B2()
```

### Rendezvous o Barrera de Sincronización (cuando A1 y B1 pasa antes que A2 y B2)
```
semaforo semaforoA = sem(0)
semaforo semaforoB = sem(0)

A():
    A1()
    permisoB.signal()
    permisoA.wait()
    A2()

B():
    B1()
    permisoA.signal()
    permisoB.wait()
    B2()
```

### Mutex (Exclusión mutua del acceso a la sección crítica)
```
semaforo mutex = sem(1)
A():
    noCrit()
    mutex.wait()
    crit()
    mutex.signal()
    noCrit()

B():
    noCrit()
    mutex.wait()
    crit()
    mutex.signal()
    noCrit()
```


### Barrera (Turnstile)
- Cada P_i, i∈[0, …, N−1]  tiene que ejecutar a a(i);b(i);
- Propiedad a garantizar:
	- b(j) se ejecuta despues de todos los a(i)
	- Queremos poner una barrera entre los a y los b pero sin restringir de más:
No hay que imponer ningún orden entre los a(i) y los b(i)
```
semaforo barrera = sem(0)
semaforo mutex = sem(1)
int counter = 0

procesos():
    funcion1()
    mutex.wait()
    counter++
    if(counter==n): barrera.signal()
    mutex.signal()

    barrera.wait()
    barrera.signal()
    funcion2
```

### Productor-Consumidor con semáforos
```
semaforo mutex = sem(1)
semaforo llenos = sem(0)
semaforo vacios = sem(n) // Capacidad del buffer

productor():
    while(true):
        item = producir_item()
        vacios.wait()
        // Hay lugar, necesito acceso exclusivo
        mutex.wait()
        agregar(item, buffer)
        cant++
        mutex.signal()
        llenos.signal()

consumidor():
    while(true):
        // Hay algo. Necesito acceso exclusivo
        mutex.wait()
        item = sacar(buffer)
        cant--
        mutex.signal()
        vacios.signal()
        hacer_algo(item)
```

### Turnos
- Tenemos una serie de procesos ejecutando en simultáneo: P_i, i ∈ [0…N−1]
- Cada proceso P_i ejecuta una tarea s_i
- Supongamos que consiste en imprimir "Soy el proceso i"
- Queremos:
    - Soy el proceso 0, Soy el proceso 1, …, Soy el proceso N−1
- Toda ejecución debe garantizar la siguiente propiedad:
    - Los s_i  ejecutan en orden: s_0, s_1, …, s_(N−1)

```
semaforo sem[N+1]
init():
    for(i = 0; i < N+1; i++):
        sem[i] = sem(0)
    for(i = 0; i < N; i++):
        spawn P(i)
    sem[0].signal()

P(i):
    sem[i].wait()
    s(i)
    sem[i+1].signal()
```