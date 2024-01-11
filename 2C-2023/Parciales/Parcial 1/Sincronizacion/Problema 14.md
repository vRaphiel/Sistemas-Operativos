The room party problem

One semester there was a controversy over an allegation by a student that someone from the Dean of Students Office had searched his room in his absence. Although the allegation was public, the Dean of Students wasn’t able to comment on the case, so we never found out what really happened. I wrote this problem to tease a friend of mine, who was the Dean of student Housing

The following synchronization constraints apply to students and the Dean of Students:
1. Any number of students can be in a room at the same time.
2. The Dean of Students can only enter a room if there are no students in the room (to conduct a search) or if there are more than 50 students in the room (to break up the party).
3. While the Dean of Students is in the room, no additional students may enter, but students may leave.
4. The Dean of Students may not leave the room until all students have left.
5. There is only one Dean of Students, so you do not have to enforce exclusion among multiple deans.
Puzzle: write synchronization code for students and for the Dean of Students that enforces all of these constraints.

estudiantesEnCuarto = 0
decano = 'no aqui'

mutex = sem(1)

barreraIngreso = sem(1)
ingresoEstudiantes = sem(0)
cuartoLimpio = sem(0)

decano:
    mutex.wait()
    si 0 < estudiantesEnCuarto < 50:
        decano = 'en espera'
        mutex.signal()
        ingresoEstudiantes.wait()

    si estudiantesEnCuarto >= 50:
        decano = 'presente'
        breakUpParty() // Desarmar la fiesta
        barreraIngreso.wait() // La barrera la bloqueo
        mutex.signal()
        cuartoLimpio.wait()
        barreraIngreso.signal()

    si no:
        buscar()

    decano = 'no aqui'
    mutex.signal()

estudiantes:
    mutex.wait()
    if decano == 'presente'
        mutex.signal()
        barreraIngreso.wait()
        barreraIngreso.signal()
        mutex.wait()

    estudiantesEnCuarto++

    if estudiantesEnCuarto == 50 y decano = 'en espera':
        ingresoEstudiantes.signal()
    else:
        mutex.signal()

    party()

    mutex.wait()
        estudiantesEnCuarto--
        if estudiantes == 0 y decano = 'en espera':
            ingresoEstudiantes.signal()
        else if estudiantesEnCuarto == 0 y decano = 'en espera':
            cuartoLimpio.signal()
        else:
            mutex.signal()