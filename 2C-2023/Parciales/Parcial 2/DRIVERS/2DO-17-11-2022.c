struct device_t {
    int pid;
    bool free;
    cola queue;
    mutex mtx;
} devices[3]

bool in_range(int device_id) {
    return 0 <= device_id && device_id < 3;
}

// Se controla el device pedido
bool match_id(int pid, int device_id) {
    return in_range(device_id) && !devices[device_id].free && devices[device_id].pid == pid;
}

void mandar_byte(int device_id) {
    if(devices[device_id].cola.empty()) return;

    char dato = devices[device_id].cola.peek(1);
    devices[device_id].cola.pop.front();

    OUT(ADDRESS_X, dato); // Colocar
}

void handler_1() {
    mandar_byte(1);
}

void handler_2() {
    mandar_byte(2);
}

void handler_3() {
    mandar_byte(3);
}

int open(int device_id) {
    // Liberar major/minor/etc.    
    if(!in_range(device_id)) return IO_ERROR;
    devices[device_id].mtx.lock(); // Espero a que esté libre
    devices[device_id].free = false;
    devices[device_id].pid = task_pid_nr(current);
    return IO_OK;
}

int close(int device_id) {
    if(!match_id(task_pid_nr(current), device_id)) return IO_ERROR;
    devices[device_id].free = true;
    devices[device_id].mtx.unlock();

    return IO_OK;
}

// El write escribe el valor en el dispositivo device_id
// En data tenemos toda la cantidad de archivos. Pero, ¿Que significa cantidad?
int write(int device_id, char* data, int cantidad) {
    if(!match_id(task_pid_nr(current), device_id)) return IO_ERROR;
    char *buffer = kmalloc(cantidad);
    copy_from_user(buffer, data, cantid);
    for(int i = 0; i < cantidad; i++) 
        devices[device_id].cola.push_back(buffer[i]);
    
    if(IN(CONTROL_X) == 0)
        mandar_byte(device_id)

    return IO_OK
}

// En driver init hay que hacer las cosas.
// Pedir major/minor y registrar. 
int driver_init() {
    bool done = false;
    while(!done) { // Todos iniciados. Busy waiting
        done |= IN(CONTROL_1) == 0 && IN(CONTROL_2) == 0 && IN(CONTROL_3) == 0;
    }
    devices[1].free = true;
    devices[2].free = true;
    devices[3].free = true;
    if(request_irq(EQUIPO_IRQ_1, handler_1) == IRQ_ERROR) return IO_ERROR;
    if(request_irq(EQUIPO_IRQ_2, handler_2) == IRQ_ERROR) return IO_ERROR;
    if(request_irq(EQUIPO_IRQ_3, handler_3) == IRQ_ERROR) return IO_ERROR;
    return IO_OK;
}

int driver_remove() {
    free_irq(EQUIPO_IRQ_1);
    free_irq(EQUIPO_IRQ_2);
    free_irq(EQUIPO_IRQ_3);
}