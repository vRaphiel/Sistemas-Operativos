The Senate Bus problem

This problem was originally based on the Senate bus at Wellesley College. Riders come to a bus stop and wait for a bus. When the bus arrives, all the waiting riders invoke boardBus, but anyone who arrives while the bus is boarding has to wait for the next bus. The capacity of the bus is 50 people; if there are more than 50 people waiting, some will have to wait for the next bus.
When all the waiting riders have boarded, the bus can invoke depart. If the bus arrives when there are no riders, it should depart immediately.
Puzzle: Write synchronization code that enforces all of these constraints

- Personas van a una parada a esperar un bus
- Cuando llega todos invocan boardBus()
- El que llegue a la parada mientras el bus esta siendo abordado, espera al siguiente
- La capacidad es de 50 personas
- Si hay más de 50 personas esperando, algunas deberán esperar al siguiente
- Cuando todos hayan subido, el bus sale. Si el bus llega y no hay pasajeros, parte inmediatamente

(1) Una barrera, llegan tantas personas. Si hay 50 o más, entonces la barrera se va a liberar cuando se cumpla (2)
(2) Llega el colectivo, se abre la barrera, suben 50. Es bloqueante, porque solo suben 50 o quienes estén. (sección critica)
(3) Todos los que queden aguardan al siguiente colectivo

enEspera = 0

mutex = sem(1)

barrera = sem(50)

barreraPuedenSubir = sem(0)
todosListos = sem(0)

pasajeros:
    barrera.wait()
        mutex.wait()
            enEspera++
        mutex.signal()

        barreraPuedenSubir.wait()
    barrera.signal()

    abordarBus()
    enEspera--
    if enEspera == 0:
        todosListos.signal()
    else
        barreraPuedenSubir.signal()

bus:
    // Llega el bus. Tengo que ver cuantos hay
    mutex.wait()
    if(enEspera > 0):
        barreraPuedenSubir.signal()
        todosListos.wait()
    mutex.signal()

    partir()
