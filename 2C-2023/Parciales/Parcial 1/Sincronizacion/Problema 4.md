The Santa Claus problem

Stand Claus sleeps in his shop at the North Pole and can only be awakened by either (1) all nine reindeer being back from their vacation in the South Pacific, or (2) some of the elves having difficulty making toys; to allow Santa to get some sleep, the elves can only wake him when three of them have problems. When three elves are having their problems solved, any other elves wishing to visit Santa must wait for those elves to return. If Santa wakes up to find three elves waiting at his shop’s door, along with the last reindeer having come back from the tropics, Santa has decided that the elves can wait until after Christmas, because it is more important to get his sleigh ready. (It is assumed that the reindeer do not want to leave the tropics, and therefore they stay there until the last possible moment.) The last reindeer to arrive must get Santa while the others wait in a warming hut before being harnessed to the sleigh

Here are some addition specifications:
• After the ninth reindeer arrives, Santa must invoke prepareSleigh, and then all nine reindeer must invoke getHitched.
• After the third elf arrives, Santa must invoke helpElves. Concurrently, all three elves should invoke getHelp.
• All three elves must invoke getHelp before any additional elves enter (increment the elf counter).
Santa should run in a loop so he can help many sets of elves. We can assume that there are exactly 9 reindeer, but there may be any number of elves

needHelp = 0
reinderBack = 0

mutex = sem(0)

reindeerBack = sem(9)
santaSleigh = sem(9)
santaHelp = sem(3);
santaSem = sem(0)
elvesSem = sem(1)

elves = []

reinder:
    mutex.wait()
    reinderBack++;
    if(reinderBack == 9):
        santaSem.signal()
    mutex.signal()
    
    santaSleight.wait()
    getHitched()
    santaSleight.signal()
    

elves:
    elvesSem.wait()

    mutex.wait()
    needHelp++;
    if(needHelp == 3):
        santaSem.signal()
    mutex.signal()
    
    santaHelp.wait()
    getHelp()

    mutex.wait()
        elves--
        if(elves == 0):
            elvesSem.signal()
    mutex.signal()

santa:
    santaSem.wait()
    mutex.wait()
        if(reinderBack == 9):
        reindeerBack.wait()
        prepareSleight()
        santaSleight.signal()
        reindeer = 0

    if(needHelp == 3):
        helpElves()
        santaHelp.signal()
    mutex.signal()
