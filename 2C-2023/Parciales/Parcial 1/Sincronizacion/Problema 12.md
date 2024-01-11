The suhi bar problem

Imagine a sushi bar with 5 seats. If you arrive while there is an empty seat, you can take a seat immediately. But if you arrive when all 5 seats are full, that means that all of them are dining together, and you will have to wait for the entire party to leave before you sit down.
Puzzle: write code for customers entering and leaving the sushi bar that enforces these requirements

- Si llegas y hay un asiento libre, te sientas.
- Si los 5 asientos estan ocupados, esperas


ocupados = 0
esperando = 0

mutex;
asientos = sem(5)

sentarse:
    mutex.wait()
    ocupados++
    esperando--
    mutex.signal()

salir:
    mutex.wait()
    ocupados--
    asientos.signal()
    mutex.signal()

cliente:
    mutex.wait()
    esperando++
    mutex.signal()

    asientos.wait()
    sentarse()
    comer()
    salir()
