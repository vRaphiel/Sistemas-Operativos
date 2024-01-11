/**
 * Escribir el código de un módulo /dev/invertir el cual funciona como:
 * - Si el usuario escribe una cadena en un dispositivo, se almacena en buffer.
 * - El buffer se invierte y se almacena en memoria del usuario
 * - Cuando el usuario lee el dispositivo, se devuelve la cadena invertida y número de caracteres
 * 
 * Funciones:
 * -> copy_to_user
 * -> copy_from_user
 * -> kmalloc
 * -> strlen
 * -> invstr
*/

// sección driver

struct palabra {
    char palabra;
    int longitud;
}

int driver_read(int * data, size_t size) {
    char * buffer;
    int i;
    buffer = kmalloc(size, GFP_KERNEL);
    i = 0
    while(i < p->longitud) {
        buffer[i] -> p->palabra[p->longitud - i];
    }
    copy_to_user(data, buffer, 1);
    return 0;
}

int driver_write(int * data, size_t size) {
    palabra *p;
    char buffer;
    copy_from_user(&buffer, data, 1);
    p->palabra = buffer;
    p->longitud = strlen(buffer);
    return size;
}

// sección usuario

struct palabra {
    char palabra;
    int longitud;
}

int main(int argc, char* argv) { 

    int driver = open('/dev/invertir');
    palabra p;

    while(1) {
        char* palabra_scan = scanf();

        write(driver, palabra_scan, sizeof(palabra_scan));
        read(driver, palabra, sizeof(palabra));

        printf("%s - %d", palabra->palabra, palabra->longitud);

    }

    return 0;
}