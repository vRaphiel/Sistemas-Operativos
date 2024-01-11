/**
 * Tenemos Ext2. Necesitamos un pseudocódigo y:
 *      void my_grep(char * palabra, char * path)
 * La función debe recibir como parámetros una palabra y una ruta a un directorio. Debe imprimir por poantalla las líneas de los archivos regulares que contienen la palabra.
 * La busqueda debe realizarse en cada subdirectorio. Salida:
 *      File.txt, linea de texto.
 * Agregar '\0' como fin de linea y EOC como fin de archivo.
 * 
*/

#define BLOCK_SIZE = 0xFFFFFF;

void my_grep(char * palabra, char* path) {
    Ext2FSInode * inode_dir = inode_for_path(path);
    char * buffer = (char *) malloc(BLOCK_SIZE);
    int num_block = 0;
    int recorrido = 0;
    while(recorrido < inode_dir->size) {
        int dir = get_block_address(inodo_dir, num_block);
        read_block(dir, num_block);
        while(offsetDirEntry < BLOCK_SIZE) {
            Ext2FSDirEntry * dir_entry = (Ext2FSDirEntry *) (buffer + offsetDirEntry);
            imprimirLS(dir_entry);
            offsetDirEntry = dir_entry->record_length;
            recorrido += dir_entry->record_length;
        }
        num_block++;
        offsetDirEntry = block_size;
    }
    free(buffer);
    return 0;
}

void imprimirLS(Ext2FSDirEntry * dirEntry, char* palabra) {
    Ext2FSInode * inodo_dir_entry = load_inode(dirEntry->inode);
    char nombre[dirEntry->name.length];
    strcpy(nombre, dirEntry->name, dirEntry->name.length);
    if(nombre == palabra) {
        printf("%s", nombre);
    }
}