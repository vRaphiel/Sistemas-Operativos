#include <mutex>       // std::mutex
#include <thread>      // std::thread
#include <semaphore.h> // POSIX semaphores
#include <atomic>      // Atomic elements (std C++11)
#include <iostream>
#include <vector>
#include <chrono>
#define BUFFER_CAPACITY 10

using namespace std::chrono;
using namespace std;

class Buffer {
    public:

        Buffer() {
            sem_init(&sem_lleno, 0, BUFFER_CAPACITY);
            sem_init(&sem_vacio, 0, 0);
            contadorConsumidor = contadorProductor = 0;
        }

        void produce(int thread_id, int num){
            //En caso de que el buffer este lleno, el productor se bloquea
            sem_wait(&sem_lleno);
                m.lock();
                    //zona critica
                    cout << "thread " << thread_id << " produce " << num << endl;
                    buffer[contadorProductor] = num;
                    contadorProductor = (contadorProductor + 1) % BUFFER_CAPACITY;
                m.unlock();
            //Avisa que el buffer no esta vacio    
            sem_post(&sem_vacio);
        }

        int consume(int thread_id){
            //En caso de que el buffer este vacio, el consumidor se bloquea
            sem_wait(&sem_vacio);
                m.lock();
                    //zona critica
                    int result = buffer[contadorConsumidor];
                    cout << "thread " << thread_id << " consume " << result << endl;
                    contadorConsumidor = (contadorConsumidor + 1) % BUFFER_CAPACITY;
                m.unlock();
            //Avisa que el buffer al menos no esta mas lleno
            sem_post(&sem_lleno);
            return result;
        }

        ~Buffer(){
            sem_destroy(&sem_lleno);
            sem_destroy(&sem_vacio);
        }
    private:
        mutex m;
        int buffer[BUFFER_CAPACITY];
        int contadorConsumidor, contadorProductor;
        sem_t sem_lleno, sem_vacio;

};

void productor(Buffer &buffer, int id){
    while(1){
        int new_int = rand() % 10 + 1;
        buffer.produce(id, new_int);
        this_thread::sleep_for(milliseconds(10));
    }   
}

void consumidor(Buffer &buffer, int id){
    while(1){
        this_thread::sleep_for(milliseconds(100));
        buffer.consume(id);
    }
}


int main() {
    std::vector<std::thread> threads(10);

    Buffer* buffer = new Buffer();
    int i = 0;
    for(auto &t : threads){
        if (i < 5) {
            t = std::thread(consumidor, ref(*buffer), i);
        } else{
            t = std::thread(productor, ref(*buffer), i);
        } 
        i++;
    }

    for(auto &t : threads){
        t.join();
    }


    
}

