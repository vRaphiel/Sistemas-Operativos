The Modus Hall Problem

After a particularly heavy snowfall this winter, the denizens of Modus Hall created a trench-like path between their cardboard shantytown and the rest of campus. Every day some of the residents walk to and from class, food and civilization via the path; we will ignore the indolent students who chose daily to drive to Tier 3. We will also ignore the direction in which pedestrians are traveling. For some unknown reason, students living in West Hall would occasionally find it necessary to venture to the Mods.
Unfortunately, the path is not wide enough to allow two people to walk side-by-side. If two Mods persons meet at some point on the path, one will gladly step aside into the neck high drift to accommodate the other. A similar situation will occur if two ResHall inhabitants cross paths. If a Mods heathen and a ResHall prude meet, however, a violent skirmish will ensue with the victors determined solely by strength of numbers; that is, the faction with the larger population will force the other to wait.

Puzzle: write code that implements categorical exclusion with majority rule.

- Solo pueden haber dos personas caminando por el mismo camino
- Si dos personas se encuentran en un punto siendo del mismo bando una se pone a un costado y la otra pasa
- Si dos personas se encuentran y son de bandos distintos, se enfrentan y gana quien tena mayor cantidad de integrantes en su grupo.
 
heathens = 0
prudes = 0
status = ’ neutral ’
mutex = Semaphore (1)
heathenTurn = Semaphore (1)
prudeTurn = Semaphore (1)
heathenQueue = Semaphore (0)
prudeQueue = Semaphore (0)

heathenTurn.wait()
heathenTurn.signal()

mutex.wait()
heathens++

if status == 'neutral':
    status = 'heathens rule'
    mutex.signal ()
elif status == 'prudes rule':
    if heathens > prudes :
    status = 'transition to heathens'
    prudeTurn.wait()
    mutex.signal()
    heathenQueue.wait()
elif status == 'transition to heathens':
    mutex.signal()
    heathenQueue.wait()
else
    mutex.signal()

# cross the field

mutex.wait()
heathens--

if heathens == 0:
    if status == 'transition to prudes':
        prudeTurn.signal()
    if prudes:
        prudeQueue.signal(prudes)
        status = 'prudes rule'
    else :
        status = 'neutral'

if status == 'heathens rule':
    if prudes > heathens :
    status = 'transition to prudes'
    heathenTurn.wait()

mutex.signal()