Se tienen n procesos que ejecutan el código. Se espera que todos los procesos terminen de ejecutar la función poreparado() antes de que alguno de ellos llame a critica().
Porque la solución permite inanicion? Modificar el código

preparado()

mutex.wait()
count = count + 1
mutex.signal()

if(count == n)
    barrera.signal()

barrera.wait()
critica()

Todos pasan el mutex y se quedan en el barrera.wait() esperando.
Cuando count == n se hace un signal() por lo tanto, uno solo pasa y todos los demás se quedan esperando.
Lo ideal sería:

preparado()

mutex.wait()
count = count + 1
if(count == n)
    barrera.signal()
mutex.signal()

barrera.wait()
barrera.signal()

critica()

De forma que uno que pasa la barrera tira un signal para despertar a otro proceso y así consecutivamente.