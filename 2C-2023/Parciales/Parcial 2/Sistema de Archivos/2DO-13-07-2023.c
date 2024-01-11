// Implementar un algoritmo de copia de archivos
// my_copy("/dir1/dir2/archivo_a_copiar.txt", "/dir3/copiado.txt")
// a - dos versiones: Ext2 y FAT
// Se tiene BLOCK_SIZE
// En Ext2 se tiene un inodo para el archivo ruta destino.

// Ext2
// La idea es buscar el inodo del archivo inicial, luego el inodo del archivo destino
/**
 * Para el archivo inicial, recorro bloque por bloque, lo voy leyendo hasta que encuentre uno vacio.
 * Esto implica tener que ir por los directos, luego los indirectos, luego los doble indirectos y finalmente el triple indirecto.
 * Por cada bloque que tengo traigo su FS y posteriormente obtendo su bloque de datos.
 * Por cada bloque de datos, para dicho inodo traigo un nodo libre del inodo destino con get_free_block_address
 * Obtenido ese inodo destino, escribo con write_block en lo que me dió get_free_block_address.
 * Paso lo necesario para terminar con ese bloque y sigo con el que le sigue.
 * 
*/

#define BLOCK_SIZE = 0xFFFF;

void my_copy(char* path1, char* path2) {
    // Lo primero a hacer es buscar el inodo del archivo inicial y el archivo destino
    Ext2FSInode * inodo_inicial = inode_for_path(path1);
    Ext2FSInode * inodo_destino = inode_for_path(path2);
    // Obtenidos los inodos del archivo, entonces ahora tengo que leer el bloque de dirección.
    // Leeré los archivos del bloque y luego los debo ir escribiendo uno a uno en el inodo.
    char* buffer = (char *) malloc(BLOCK_SIZE);
    int num_block = 0;
    int recorrido = 0;
    int num_block = 0;
    while(recorrido < inodo_inicial->size) {
        int dir1 = get_block_address(inodo_inicial, num_block);
        read_block(dir1, buffer);
        // Voy recorriendo los bloques
        while(offsetDirEntry < BLOCK_SIZE) {
            dirEntry* dirEntry = (dirEntry *) buffer + offsetDirEntry;
            Ext2FSInode * inodo_dir_entry = load_inode(dirEntry->inode);

            // Tengo el inodo con el número.
            int nuevaDir = get_free_block_address(inodo_destino);
            write_block(nueva_dir, buffer);
            add_block_address_to_inode(inodo_dir_entry, nueva_dir, dirEntry->block_number);
            offsetDirEntry = dirEntry->record_length;
            recorrido += dirEntry->record_length;
            offsetDirEntry = BLOCK_SIZE;
        }
        num_block++;
    }
}

// FAT
/**
 * Se cuenta con un bloque disponible para el comienzo del archivo a copiar. Se puede acceder a FAT como un arreglo.
*/
void my_copy(char* path1, char* path2) {
    int pos_archivo_copiar = get_init_block_for_path(path1);
    int pos_archivo_pegar = get_init_block_for_path(path2);
    // Se que la FAT avanza hasta que encuentre un EOF
    // Itero mientras no encuentre un EOF. Como las entradas de FAT son Block, Contenido, Siguiente hago eso
    char * buffer;
    int num_block_copy = pos_archivo_copiar;
    int num_block_paste = pos_archivo_pegar;

    while(FAT[num_block_copy]->next != EOF) {
        read_block(FAT[num_block_copy]->block_address, buffer);
    
        if(FAT[num_block_copy]->next == EOF) {
            buffer->next = EOF
            write_block(prox_destiny, buffer)
        } else {
            int prox_destiny = get_free_block_address();
            buffer->next = prox_destiny;
            write_block(prox_destiny, buffer);
        }
        // Obtengo la siguiente posición libre. Ahora, tengo que hacer lo siguiente
        num_block_copy = FAT[num_block_copy]->next;
    }
}
