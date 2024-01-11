The roller coaster problem

Suppose there are n passenger threads and a car thread. The passengers repeatedly wait to take rides in the car, which can hold C passengers, where C < n. The car can go around the tracks only when it is full.

Here are some additional details:
• Passengers should invoke board and unboard.
• The car should invoke load, run and unload.
• Passengers cannot board until the car has invoked load
• The car cannot depart until C passengers have boarded.
• Passengers cannot unboard until the car has invoked unload.
Puzzle: Write code for the passengers and car that enforces these constraints.

inCar = 0
passenger = 0

pasajerosListos = sem(0)
permiteSubir = sem(0)
permiteBajar = sem(0)
listosCar = sem(0)

passenger:

    mutex.wait()
    passenger++;
    if(passenger >= C):
        pasajerosListos.signal()
    mutex.signal()

    permiteSubir.wait()
    board()

    mutex.wait()
    passenger--
    inCar++
    mutex.signal()

    permiteBajar.wait()
    unboard()


car:
    pasajerosListos.wait()

    load()
    permiteSubir.signal(C)

    mutex.wait()
    if(inCar == C):
        inCar = 0
        listosCar.signal()
    mutex.signal()

    listosCar.wait()
    run()

    unload()
    permiteBajar.signal(C)


