The barbeshop Problem (P 121)
A barbershop consists of a waiting room with n chairs, and the barber room containing the barber chair. If there are no customers to be served, the barber goes to sleep. If a customer enters the barbershop and all chairs are occupied, then the customer leaves the shop. If the barber is busy, but chairs are available, then the customer sits in one of the free chairs. If the barber is asleep, the customer wakes up the barber. Write a program to coordinate the barber and the customers.
To make the problem a little more concrete, I added the following information:
• Customer threads should invoke a function named getHairCut.
• If a customer thread arrives when the shop is full, it can invoke balk, which does not return.
• The barber thread should invoke cutHair.
• When the barber invokes cutHair there should be exactly one thread invoking getHairCut concurrently.
Write a solution that guarantees these constraints.

- N sillas + Silla del barbero
- Si no hay clientes el barbero duerme
- Si un cliente entra a la barberia y las sillas estan ocupadas el cliente se va
- Si el barbero esta ocupado pero hay sillas el cliente ocupa una de las libres
- Si el barbero esta durmiendo, el cliente lo despierta

sillas = 0
mutex = Semaphore (1)
customer = Semaphore (0)
barber = Semaphore (0)
customerDone = Semaphore (0)
barberDone = Semaphore (0)

cliente:

    mutex.wait()
    if(sillas == N):
        mutex.signal()
        balk()
    customers+=1
    mutex.signal()

    customer.signal()
    barber.wait()

    getHairCut()

    customerDone.signal()
    barberDone.wait()

    mutex.wait()
    sillas = sillas - 1
    mutex.signal()

barbero:
    customer.wait()
    barber.signal()

    cutHair()

    customerDone.wait()
    barberDone.signal()


Generalización FIFO:
In the previous solution there is no guarantee that customers are served in the order they arrive. Up to n customers can pass the turnstile, signal customer
and wait on barber. When the barber signal barber, any of the customers might proceed.
Modify this solution so that customers are served in the order they pass the turnstile.
Hint: you can refer to the current thread as self, so if you write self.sem = Semaphore(0), each thread gets its own semaphore.

n = 4
customers = 0
mutex = Semaphore (1)
customer = Semaphore (0)
customerDone = Semaphore (0)
barberDone = Semaphore (0)
queue = []

cliente:
    self.sem = Semaphore(0)
    mutex.wait()
    if customers == n:
        mutex.signal ()
        balk ()
    customers += 1
    queue.append(self.sem)
    mutex.signal()

    customer.signal ()
    self.sem.wait ()

    # getHairCut ()

    customerDone.signal()
    barberDone.wait()

    mutex.wait()
    customers -= 1
    mutex.signal()

barbero:
    customer.wait()
    mutex.wait()
    sem = queue.pop(0)
    mutex.signal()

    sem.signal()

    #cutHair()

    customerDone.wait()
    barberDone.signal()