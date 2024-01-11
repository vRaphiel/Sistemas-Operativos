The child care problem

At a child care center, state regulations require that there is always one adult present for every three children.
Puzzle: Write code for child threads and adult threads that enforces this constraint in a critical section

// MI SOLUCIÓN 

childs = 0
parents = 0
espera = 0
saliendo = 0

childSem = sem(0)
parentSem = sem(0)

child:
    mutex.wait()
    if childs > 3*adults:
        espera++
        mutex.signal()
        childSem.signal()
    else:
        childs++
        mutex.signal()
        
    parentSem.wait()

    # HACER COSAS

    mutex.wait()
    childs--
    if saliendo <= 3*(adults - 1) && childs <= 3*(adults - 1):
        saliendo--
        adults--
        parentSem.wait()
    mutex.signal()

parents:
    mutex.wait()
    if espera:
        n = min(3, espera)
        parentSem.signal(n)
        espera -= n
        childs += n
    mutex.signal()

    childSem.wait()

    mutex.wait()
    if childs <= 3 * (adults - 1):
        adults--
        mutex.signal()
    else:
        saliendo++
        mutex.signal()
        childSem.wait()
