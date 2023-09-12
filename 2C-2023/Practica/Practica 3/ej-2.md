Se tiene un sistema con 4 procesos accediendo a una variable compartida x y un mutex.
El código lo ejecutan 4 procesos. Del valor de la variable dependen ciertas decisiones que toma cada proceso.
Se debe asegurar que cada vez que un proceso lee de la variable compartida previamente solicita el mutex y luego lo libera.
¿Los procesos cumplen con lo planteado?
¿Puede ocurrir Race Condition?

x = 0
mutex(1)

while(1) {
    mutex.wait()
        y = x;
    mutex.signal()
    if y <= 5 {
        x++;
    } else {
        x--;
    }
}

Si hay que asignar el valor a la variable Y si cumplen lo pedido, puesto que todas siempre van a asignar a Y el valor de X.
Ahora, no ocurre especificamente que cada proceso incremente en 1 y que cuando vuelva al primer proceso sea X + 4.
Esto se debe a que un proceso puede consultar en el IF y <= 5 y el Y sea 5 justamente y pase a incrementar pero otro proceso cambie y lo consulte tambien.
Allí la Y sigue siendo 5, pero este tiene tiempo suficiente como para disminuirle un valor y para actualizar el valor de Y.
Cuando vuelve al proceso anterior Y ahora es 6, no debería entrar en la condición de Y <= 5 porque Y debería ser 6 puesto que X cambió.
Entonces incrementa un valor, cuando debería restarlo.

No cumple con lo planteado.
Hay race condition. El valor de X puede ser modificado en instancias donde no debería ocurrir.
