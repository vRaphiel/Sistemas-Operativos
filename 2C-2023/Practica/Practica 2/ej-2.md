Sean P0, P1 y P1 tales que
- P0 tiene rafagas cortas de E/S
- P1 frecuentemente se bloquea leyendo de la red
- P2 tiene ráfagas prolongadas de alto consumo de CPU y luego de escritura a disco

a - Para planificar estos procesos ¿Convendría usar un algoritmo de RR? ¿Convendria usar uno de prioridades? Justificar
Round Robin es una lista que asigna Quantum a cada proceso y procede a resolver las cosas.
Si el proceso se bloquea igualmente consume el quantum. Si el proceso escribe necesita prioridad para terminar.
Las rafagas cortas de E/S ocuparán el mismo quantum como mucho
No conviene RR.

Prioridades convendría.
Con una E/S se le da prioridad máxima y sigue.
La escritura se le da prioridad y se escribe
Luego cuando no haya nada se corre P1 para liberar todos los procesos
