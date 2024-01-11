The Dinning Savages Problem (P 115)
A tribe of savages eats communal dinners from a large pot that can hold M servings of stewed missionary. 
When a savage wants to eat, he helps himself from the pot, unless it is  emmpty. 
If the pot is empty, the savage wakes up the cook and then waits until the cook has refilled the pot.

Any number of savage threads run the following code:
savage code:
    while True:
        getServingFromPot()
        eat()
One cook run this code:
cook code:
    while True:
        putServingsInPot(M)

The synchronization constraints are:
• Savages cannot invoke getServingFromPot if the pot is empty.
• The cook can invoke putServingsInPot only if the pot is empty.
Puzzle: Add code for the savages and the cook that satisfies the synchronization constraints.

- Tenemos M personas y 1 solo plato
- Cuando una persona agarra del plato nadie más puede agarrar (Mutex)
- Si el plato está vacio, anuncia que vaya a servirse
- Mientras se sirve nadie puede tomar
- Se reanuda

mutex m;
sem savage(M)
sem food();
atomic stewed = M;

savage code:
    while True:
        savage.wait()
        m.wait()
        getServingFromPot()
        stewed = stewed - 1
        if(stewed == 0) {
            food.signal();
        }
        m.signal()

cook code:
    while True:
        food.wait()
        putServingsInPot(M)
        stewed = M
        savage.signal(M)
        
    