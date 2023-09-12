Suponer que se tienen N procesos Pi. Cada uno de lso cuales ejecuta un conjunto de sentencias ai y bi
¿Como se pueden sincronizar estos procesos de manera tal que los bi se ejecuten despues de que se hayan ejecutado todos los ai?

Con molinete

mutex = sem(0)
semaforo = sem(0)
counter = 0

proceso():
    
    a()

    mutex.wait()
    counter++
    if(counter == n)
        semaforo.signal()
    mutex.signal()

    semaforo.wait()
    semaforo.signal()

    b()
