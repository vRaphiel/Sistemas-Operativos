The Faneuil Hall problem

There are three kinds of threads: immigrants, spectators, and a one judge:

- Immigrants must wait in line, check in, and then sit down.
- At some point, the judge enters the building. When the judge is in the building, no one may enter, and the immigrants may not leave. 
- Spectators may leave. 
- Once all immigrants check in, the judge can confirm the naturalization. 
- After the confirmation, the immigrants pick up their certificates of U.S. Citizenship. 
- the judge leaves at some point after the confirmation. 
- Spectators may now enter as before. 
- After immigrants get their certificates, they may leave

To make these requirements more specific, let’s give the threads some functions to execute, and put constraints on those functions.
• Immigrants must invoke enter, checkIn, sitDown, swear, getCertificate and leave.
• The judge invokes enter, confirm and leave.
• Spectators invoke enter, spectate and leave.
• While the judge is in the building, no one may enter and immigrants may not leave.
• The judge can not confirm until all immigrants who have invoked enter have also invoked checkIn.
• Immigrants can not getCertificate until the judge has executed confirm.

judgeInBuild = 'en sesion'
inmigrantes = 0
espectadores = 0

barreraIngreso = sem(n)
barreraListaEspera = sem(0)
barreraCheckIn = sem(0)
barreraIngresoEspectadores = sem(0)

inmingrants:
    barreraIngreso.wait()

    enter()
    mutex.wait()
    inmigrantes++
    if inmigrantes == n:
        barreraListaEspera.signal()
    mutex.signal()

    barreraListaEspera.wait()
    barreraListaEspera.signal()

    checkIn()
    sitDown()

    mutex.wait()
    inmigrantes--
    if inmigrantes == 0:
        barreraCheckIn.signal()
    mutex.signal()

    barreraJurado.wait()

    swear()
    getCertificate()

    mutex.wait()
    inmigrantes++
    if inmigrantes == n:
        barreraIngreso.signal()
    mutex.signal()

    barreraIngreso.wait()
    barreraSalida.signal()

    leave()
    
spectators:
    jurado.wait()
    enter()
    jurado.signal()
    spectate()
    leave()

judge:
    enter()

    barreraCheckIn.wait()

    mutex.wait()
    confirm()
    mutex.signal()

    barreraJurado.signal(n)
    barreraIngresoEspectadores.signal(espectadores)
    leave()
