#include <mutex>       // std::mutex
#include <thread>      // std::thread
#include <semaphore.h> // POSIX semaphores
#include <atomic>      // Atomic elements (std C++11)
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

void sumador(std::atomic<int> &sum) { 
    for (int i = 0; i < 100000; i++) {
        sum.fetch_add(1);
    }
    
    cout << "Hola mi suma es: " << sum.load() << endl;
}

void crear_asignar_threads(vector<thread> &threads, atomic<int> &suma){
    //Creo los threads
    for (auto &t : threads) { 
        //Recordar que ref se utiliza para mantener una referencia de la variable pasada
        t = std::thread(sumador, std::ref(suma)); 
    }
}

//Hago join de los threads, de esta forma espero que terminen
void join_threads(vector<thread> &threads){
    for (auto &t : threads) { 
        t.join();
    }
}

int main() {
    vector<thread> threads(10);

    atomic<int> suma{0};
    
    crear_asignar_threads(threads, suma);  
    join_threads(threads);
   
    cout << "Suma total: " << suma.load() << endl;  

    return 0;
}

