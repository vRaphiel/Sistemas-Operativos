// Ejercicio 2
void driver_load(){
    OUT(CHRONO_CURRENT_TIME, 0);
}

void driver_unload(){
    OUT(CHRONO_CURRENT_TIME, 0);
}

int dirver_open() {
    
}

void driver_close() {
    
}

int driver_read(){
}

int driver_write() {
}

// Ejercicio 3
void driver_load() {
    OUT(BTN_STATUS1, 1);
}

void driver_unload() {
    OUT(BTN_STATUS1, 0);
}

int driver_write() {
    int PRESS = IN(BTN_STATUS0)
    while(PRESS != 0) {}
    return BTN_PRESSED;
}

// Ejercicio 4
void handler(){
    if(esperando && IN(BTN_INT) == 1){
        esperando = false;
        listo.signal();
    }
    return BTN_PRESSED;
}  

void driver_load() {
    acceso = mutex_create();
    listo = semaforo.create(0);
    bool esperando = false;
    OUT(BTN_STATUS1, 1);
    irq_handler(7, handler);
}

void driver_unload() {
    OUT(BTN_STATUS1, 0);
}

int driver_write() {
    int PRESS = IN(BTN_STATUS0) 
    
    acceso.lock();
    esperando = true;
    if(PRESS == 1){
        OUT(BTN_INT, BTN_PRESSED);
        listo.wait();
    }
    acceso.unlock();

    while (PRESS != 0) {}
    return BTN_PRESSED;
}

// Ejercicio 7
/**
 * Se requiere controlar discos opticos.
 * Se posee 3 registros de lectura y 3 de escritura.
 * 
 * LECTURA:
 * - DOR_IO: Enciende o Apaga el motor de la unidad. (1 | 0).
 * - ARM: Número de pista a seleccionar.
 * - SEEK_SECTOR: Número de sector a seleccionar dentro de la pista.
 * 
 * ESCRITURA:
 * - DOR_STATUS: Contiene 0 si el motor está apagado, 1 si está encendido.
 * - ARM_STATUS: Contiene el valor 0 si el brazo se está moviendo, 1 si se ubica en la pista indicada en ARM.
 * - DATA_READY: Contiene 1 si el dato fue enviado.
 * 
 * Funciones Auxiliares
 * - int cantidad_sectores_por_pista(): Deuvelve la cantidad de sectores por cada pista del disco. El sector 0 es el primer sector de la pista.
 * - void escribir_datos(void *src): Escribe los datos apuntados por src en el último sector seleccionado.
 * - void sleep(int ms): Espera durante ms milisegundos
 * 
 * Antes de escribir un sector:
 * - El driver debe asegurarse que el motor se encuentre encendido.
 * - Si no lo está, debe encenderlo.
 *      - Para garantizar que la velocidad rotacional sea suficiente, debe esperar al menos 50ms antes de realizar cualquier operacion.
 * - Para conservar energia, cuando se finaliza una operación, el motor debe ser apagado.
 * - El apagado demora <= 200ms.
*/

// a) 
int driver_write(int sector, void *data){
    int motor_estado = IN(DOR_STATUS);
    if(motor_estado == 1){
        // Nos aseguramos, por las dudas que esté encendido
        sleep(50);      
    } else {
        sleep(200);
        // Está en proceso de apagado, entonces lo encendemos
        OUT(DOR_IO, 1);
        sleep(50);
    }

    int pistas = cantidad_sectores_por_pista();
    int pista_num = 0;
    while(sector >= pistas){
        pista_num++;
        sector = sector - pistas;
    }

    OUT(ARM, pista_num);
    OUT(SEEK_SECTOR, sector);

    int arm_state = IN(ARM_STATUS);
    while(arm_state != 0) {}

    escribir_datos(data);

    int is_ready = IN(DATA_READY);
    while(is_ready != 1){}
    OUT(DOR_IO, 0);
}

// b)


// Ejercicio 8
/**
 * Ingresar en el registro de 32 bits LOC_TEXT_POINTER la dirección de memoria donde empieza el buffer que contiene el string a imprimir
 * Ingresar en el registro de 32 bits LOC_TEXT_SIZE la cantidad de caracteres que se deben leer del buffer
 * Colocar la constante START en el registro LOC_CTRL
 * 
 * 
**/

int driver_init() {
    
}

int driver_remover() {

}

int driver_write(void *data) {

}
