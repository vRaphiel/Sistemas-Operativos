Considerar cada uno de los siguienters enunciados, para cada caso, escribir el código que permita la ejecución de los procesos según la forma de sincronización planteada utilizando semaforos. Argumentar porque cada solución evita la inanición

1. 3 procesos. A B y C. Se desea que el orden de ejecución sea alfabetico. ABC, ABC, ABC, ETC.

permisoA = sem(1)
permisoB = sem(0)
permisoC = sem(0)
mutex = sem(1)

while(1):
    permisoA.wait()
    mutex.wait()
    A()
    mutex.signal()
    permisoB.signal()

    permisoB.wait()
    mutex.wait()
    B()
    mutex.signal()
    permisoC.signal()

    permisoC.wait()
    mutex.wait()
    C()
    mutex.signal()
    permisoA.signal()

Cada proceso se ejecuta luego de que su semaforo sea activado. Al ocurrir esto se ingresa en el mutex por lo cual el proceso hace su ejecución correcta antes de poder levantar el siguiente semaforo.
Luego cada proceso se ejecuta secuencialmente, llegando al C y haciendo un signal de A tal que siempre se ejecute cada proceso antes de liberar el siguiente

2. Idem anterior pero se desea que la secuencia normal sea BBCA, BBCA, BBCA

permisoA = sem(0)
permisoB = sem(1)
permisoC = sem(0)


while(1):
    permisoB.wait()
    B()
    B()
    permisoC.signal()

    permisoC.wait()
    C()
    permisoA.signal()

    permisoA.wait()
    A()
    permisoB.signal()

3. Se tiene un productor (A) y dos consumidores (B y C) que actuan deterministicamente. La información provista por el productor debe ser retirada siempre 2 veces.
Las secuencias son: ABB, ABC, ACB, ACC

permisoA = sem(1)
permisoC = sem(2)

productor()
    permisoA.wait()
    A()
    permisoC.signal(2)

consumidor1()
    permisoC.wait()
    B()
    permisoA.signal()

consumidor2()
    permisoC.wait()
    C()
    permisoA.signal()

4. Se tienen un productor y dos consumidores. Cuando C retira la información, la retira dos veces. Los receptores actúan en forma alternada.
Secuencia normal: ABB, AC, ABB, AC, ABB, AC

permisoA = sem(1)
permisoB = sem(0)
permisoC = sem(0)
done = 0

productor():
    permisoA.wait()
    A()
    if(done == 0)
        done++
    else:
        done--
    permisoB.signal()

consumidor1()
    permisoB.wait()
    if(done == 0):
        B()
        B()
    permisoA.signal()

consumidor2()
    permisoC.wait()
    if(done == 1):
        C()
    permisoA.signal()
