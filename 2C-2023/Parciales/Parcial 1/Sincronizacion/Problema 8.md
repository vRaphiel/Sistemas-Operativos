The search-insert-delete problem

Three kinds of threads share access to a singly-linked list:
    searchers, inserters and deleters. 
Searchers merely examine the list; hence they can execute concurrently with each other. 
Inserters add new items to the end of the list; insertions must be mutually exclusive to preclude two inserters from inserting new items at about the same time. However, one insert can proceed in parallel with any number of searches. 
Finally, deleters remove items from any where in the list. At most one deleter process can access the list at a time, and deletion must also be mutually exclusive with searches and insertions.

Puzzle: write code for searchers, inserters and deleters that enforces this kind of three-way categorical mutual exclusion.

list = list<T>

searchers:

    deleteSem.wait()
    // Recipt search value
    position = 0
    while(position == sizeof(list)):
        retornar(list(position))
    

inserters:    
    deleteSem.wait()
    inserterSem.wait()

    mutexInsert.wait()
    insert()
    mutexInsert.signal()

    inserterSem.signal()

deleters:

    deleteSem.signal()
    mutexDelete.wait()
    deleteElement()
    mutexDelete.signal()
