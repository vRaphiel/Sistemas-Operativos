Se tiene una modificación de RR en la que un mismo proceso puede estar encolado varias veces en la lista de procesos Ready.

a - Puede provocar innanición ya un proceso puede estar encolada varias veces.
Siendo P1, P2, P3, P4 siendo P1,P1,P1,P1,P1,...,P1,etc.

b - Como ventajas se puede poner una prioridad mayor al proceso necesario y este puede terminar antes encolandolo varias veces y luego que continue el scheduling.
Como desventajas se produce inanición o cuello de botella al tener esto habilitado.

c- Intercalar. Los procesos que se deban encolar varias veces se intercalen.
Ej: P1,P2,P3,P4
P1,P2,P1,P3,P1,P4,P1,P2,P3,P2,P3,etc.
