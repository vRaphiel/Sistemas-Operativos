Cambiar la solución anterior con algo basado en atómico.

a - Cual genera un código más eficiente
b - Cual de ellas es más eficiente ¿Porque?
c - Que soprote requiere cada una de ellas del SO y del HW

atomic count;
count = 0

preparado()

mutex.wait()
count = count + 1;
if(count == 1):
    barrera.signal()
mutex.signal()

barrera.wait()
barrera.signal()

critica()

// Como sería con atómicas?