Hilzer’s Barbershop problem
Our barbershop has three chairs, three barbers, and a waiting area that can accommodate four customers on a sofa and that has standing room for additional customers. Fire codes limit the total number of customers in the shop to 20.
A customer will not enter the shop if it is filled to capacity with other customers. Once inside, the customer takes a seat on the sofa or stands if the sofa is filled. When a barber is free, the customer that has been on the sofa the longest is served and, if there are any standing customers, the one that has been in the shop the longest takes a seat on the sofa. When a customer’s haircut is finished, any barber can accept payment, but because there is only one cash register, payment is accepted for one customer at a time. The barbers divide their time among cutting hair, accepting payment, and sleeping in their chair waiting for a customer

In other words, the following synchronization constraints apply:
• Customers invoke the following functions in order: enterShop, sitOnSofa, getHairCut, pay.
• Barbers invoke cutHair and acceptPayment.
• Customers cannot invoke enterShop if the shop is at capacity.
• If the sofa is full, an arriving customer cannot invoke sitOnSofa.
• When a customer invokes getHairCut there should be a corresponding barber executing cutHair concurrently, and vice versa.
• It should be possible for up to three customers to execute getHairCut concurrently, and up to three barbers to execute cutHair concurrently.
• The customer has to pay before the barber can acceptPayment.
• The barber must acceptPayment before the customer can exit.
Puzzle: Write code that enforces the synchronization constraints for Hilzer’s barbershop.

El cliente:
- Entra a la tienda: enterShop()
- Se sienta: sitOnSofa() solo si enSofa < capacidadSofa
- Se corta el pelo: getHairCut()
- Paga: pay()

El barbero:
- Corta el pelo: cutHair()
- Acepta el pago: acceptPayment() // Sección Crítica

capacidad = n
enTienda = 0

capacidadSofa = m
enSofa = 0

clientesEnSofa = sem(0)
clientesEnEspera = sem(0)

barberosListos = sem(3)
barberosCortando = sem(0)
clientesCortando = sem(0)
clientesPreparados = sem(3)
willPay = sem(0)

listaSofa = []
listaEspera = []

cliente:

    mutex.wait()
    if(enTienda < capacidad):
        enterShop()
        add(queue, cliente);
        enTienda++
        mutex.signal()
        
        mutex.wait()
        if(enSofa < capacidadSofa):
            sitOnSofa()
            mutex.signal()
            
            clientePreparado.wait()
            getHairCut()

            mutex.wait()
            pay()
            willPay.signal()
            mutex.signal()

        mutex.signal()
        
    else:
        mutex.signal()


barbero:
    barberoListo.wait()
    clientePreparado.signal()

    cutHair()

    willPay.wait()
    mutex.wait()
    acceptPayment()
    mutex.signal()

    clientePreparado.wait()
    barberoListo.signal()