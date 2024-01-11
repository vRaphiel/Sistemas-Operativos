The unisex bathroom problem

She was working in a cubicle in the basement of a concrete monolith, and the nearest women’s bathroom was two floors up. She proposed to the Uberboss that they convert the men’s bathroom on her floor to a unisex bathroom, sort of like on Ally McBeal.
The Uberboss agreed, provided that the following synchronization constraints can be maintained:
• There cannot be men and women in the bathroom at the same time.
• There should never be more than three employees squandering company time in the bathroom.
Of course the solution should avoid deadlock. For now, though, don’t worry about starvation. You may assume that the bathroom is equipped with all the semaphores you need.

enBanio = 0
hombres = false
mujeres = false

mutex m;
sePuedeEntrar = sem(1)

hombre:
    sePuedeEntrar.wait()

    mutex.wait()
    enBanio++
    if(enBanio == 3):
        hombres = true
    mutex.signal()

    mutex.wait()
    enBanio--
    if(enBanio == 0):
        hombres = false
    mutex.signal()

mujer:
    sePuedeEntrar.wait()

    mutex.wait()
    enBanio++
    if(enBanio == 3):
        mujeres = true
    mutex.signal()

    mutex.wait()
    enBanio--
    if(enBanio == 0):
        mujeres = false
    mutex.signal()
