// Driver de Sensor
/**
 * Operaciones:
 *  Read: Indica al usuario cuando uno de los sensores genera error por si/no detectar la linea
 * 
 * Registros:
 *  - SENSOR_IZQ
 *  - SENSOR_CEN
 *  - SENSOR_DER 
 *  
*/

handler() {
    sem.signal();
}

init() {
    sem = sem(0);
    map_irq(INT_SENSOR_IZQ, handler);
    map_irq(!INT_SENSOR_CENTER, handler);
    map_irq(INT_SENSOR_DER, handler);
}

int driver_read(int device_id, char* data, int cantidad) {

    sem.wait();

    detect_sensor d;
    d.izquierda = IN(IZQUIERDA);
    d.centro = IN(CENTRO);
    d.derecha = IN(DERECHA);
    copy_to_user(data, &d, sizeof(detect_sensor));
    return sizeof(d);
}

// Driver Ruedas
/**
 * Operaciones:
 *  Write: Escribe en el motor I que velocidad debe tomar.
 * Registros:
 *  VELOCIDAD: 1, 2 para el motor
*/
int driver_write(int device_id, char* data, int cantidad) {
    velocidad_motor v;
    copy_from_user(data, &v, sizeof(velocidad_motor));
    OUT(MOTOR_IZQ, v.izq);
    OUT(MOTOR_DER, v_der);

    return sizeof(ubicacion);
}

/**
 * TODO:
*/

struct velocidad_motor {
    int izq;
    int der;
}

struct detect_sensor {
    int izquierda;
    int centro;
    int derecha;
}

void main() {
    int SENSORES = open("/dev/sensor");
    int RUEDITAS = open("/dev/ruedas");
    velocidad_motor vm = {
        izq: 0,
        der: 0
    }
    while(1) {
        detect_sensor p = {
            int izquierda: 0,
            int centro: 1,
            int derecha: 0,
        }

        read(SENSORES, p, sizeof(p));
        if(p.centro == 0) {
            if(p.izquierda == 1) {
                vm.izq = 1,
                vm.der = 0;
            }
            if(p.derecha == 1) {
                vm.izq = 0;
                vm.der = 1;
            }
        } else {
            vm.izq = 0;
            vm.der = 0;
        }

        write(RUEDITAS, vm, sizeof(velocidad_motor));
    }
}