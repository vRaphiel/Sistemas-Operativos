Implementar:

datos = cargar_archivo(directorios[])

Tenemos:
- FAT_entry(block_address): Devuelve la entrada de la tabla FAT de posición block_address
- raw_data = read_blocks(block_address1, block_address2, ...): Lee del disco todos los bloques indicados por parámetro en orden
- parse_directory_entries(raw_data): Devuelve una lista de struct_entrada_directorio que representa las entradas de directorio del directorio pasado en raw_data
- raw_data = root_table(): Devuelve los datos de la tabla de directorios de root

a. Enumerar tres campos que debe tener el filesystem la estructura struct_entrada_directorio
- Tipo: Para distringuir entre archivos, directorios y otros
- Nombre: Único dentro del directorio (8+3 en FAT32)
- Primer bloque del cluster (Para cargar los datos y seguir el cluster en la FAT)

b. Pseudocódigo
Necesitamos leer primero el root y luego tenemos que encontrar el archivo.

CARGAR_ARCHIVO(directorios[]):
    raw_data <- root_table()
    for name in directorios:
        dir = parse_directory_entries(raw_data)
        // Tengo parseada toda la información, necesito encontrar la entrada del directorio
        entry = find_entry(dir, name)
        if entry = NULL
            return NULL
        blocks = get_blocks(entry)
        raw_data = read_blocks(blocks)
    return raw_data

FIND_ENTRY(dir, name):
    for entry in dir:
        if entry.name = name:
            return entry

GET_BLOCKS(entry):
    last_block <- entry.firstBlock
    blocks = [last_block]
    while True
        last_block <- FAT_entry(last_block)
        if last_block = 0:
            break;
        else
            blocks.append(last_block)
    return blocks