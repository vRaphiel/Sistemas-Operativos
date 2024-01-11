tablas = sem(N)
tornillos = sem(M)
clavos = sem(K)
#tablas = 0
#tornillos = 0
#clavos = 0
mutex = sem(1)

tabla:
    mutex.wait()

    mutex.signal()

    tablas.wait()
    

tornillo:
    mutex.wait()

    mutex.signal()

clavo:
    mutex.wait()

    mutex.signal()
