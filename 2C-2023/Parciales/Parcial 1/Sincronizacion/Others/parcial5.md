Bote con capacidad de 4 seres.
Prohibido:
- 3 lobos y 1 cabra
- 3 cabras y 1 lobo
Permitido:
- 2 cabras y 2 lobos

Cuando todos abordan: abordar()
Uno puede tomar los remos: remar()

// Hay 4 lobos se aborda y rema
// Hay 4 ovejas se aborda y rema
// Hay 2 y 2 se aborda y rema

#lobos = #cabras = 0
rema = false

lobitos = sem(2)
cabritas = sem(2)
mutex = sem(1)

barrera = sem(4)

lobos:
    mutex.wait()
    #lobos++
    if #lobos == 4:
        #lobos = 0
        lobitos.signal(4)
        remero = true

    if #lobos == 2 && #cabras >= 2:
        lobos = 0
        cabras = cabras - 2
        lobitos.signal(2)
        cabritas.signal(2)
        remero = true
    else:
        mutex.signal()

    # critico
    lobitos.wait()
    abrodar()
    barrera.wait()

    if remero:
        remar()
        remero = false
        mutex.signal()

cabras:
    mutex.wait()
    #cabras++
    if #cabras == 4:
        #cabras = 0
        cabritas.signal(4)
        remero = true

    if #cabras == 2 && #cabras >= 2:
        cabras = 0
        cabras = cabras - 2
        cabritas.signal(2)
        lobitos.signal(2)
        remero = true
    else:
        mutex.signal()

    # critico
    cabritas.wait()
    abrodar()
    barrera.wait()

    if remero:
        remar()
        remero = false
        mutex.signal()