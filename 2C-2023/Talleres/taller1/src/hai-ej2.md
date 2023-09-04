### Archivo de Ejercicio 2

¿Cuántos procesos se lanzan y qué comportamiento se puede observar de cada uno?

Se lanza 1 proceso que ejecuta un fork. Este fork tiene un handler definido en la señal SIG_DFL.
Hace un sleep y luego Un write.
Luego ejecuta un Kill con SIGURG y un mensaje de "Ya Va!"
Finaliza con un "Imprimir este texto" reciviendo un SIGINT.

¿Utilizan los procesos alguna forma de IPC?¿Cuál es y para qué se usa en este caso?

Si, utiliza handlers.

¿Qué puede deducir del programa a partir de las syscalls observadas?

Utiliza fork(), write(), sleep(), handler()    