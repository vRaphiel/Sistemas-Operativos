#include <mutex>       // std::mutex
#include <thread>      // std::thread
#include <semaphore.h> // POSIX semaphores
#include <atomic>      // Atomic elements (std C++11)
#include <iostream>
#include <vector>
#include <chrono>
#include <condition_variable>
#define BUFFER_CAPACITY 10

using namespace std::chrono;
using namespace std;

class Buffer {
    public:

        Buffer() {
            sem_init(&sem_lleno, 0, BUFFER_CAPACITY);
            sem_init(&sem_vacio, 0, 0);
            contadorConsumidor = contadorProductor = buffer_size = 0;
        }

        void produce(int thread_id, int num){
            unique_lock<mutex> ul(lock);
            cvLleno.wait(ul, [&](){
                return buffer_size != BUFFER_CAPACITY;
            });

            m.lock();
            zonaCriticaProductor(thread_id, num);
            m.unlock();

            cvVacio.notify_one();
        }
        int consume(int thread_id){
            unique_lock<mutex> ul(lock);
            cvVacio.wait(ul, [&](){
                return buffer_size != 0;
            });

            m.lock();
            int result = zonaCriticaConsumidor(thread_id); 
            m.unlock();

            cvLleno.notify_one();
            return result;
        }
        ~Buffer(){
            sem_destroy(&sem_lleno);
            sem_destroy(&sem_vacio);
        }
    private:

        mutex m, lock;
        int buffer[BUFFER_CAPACITY];
        int contadorConsumidor, contadorProductor;
        int buffer_size;
        condition_variable cvLleno, cvVacio;
        sem_t sem_lleno, sem_vacio;

        void zonaCriticaProductor(int thread_id, int num){
            buffer[contadorProductor] = num;
            contadorProductor = (contadorProductor + 1) % BUFFER_CAPACITY;
            cout << "thread " << thread_id << " produce " << num << endl;
            buffer_size++;
        }

        int zonaCriticaConsumidor(int thread_id){
            int result = buffer[contadorConsumidor];
            cout << "thread " << thread_id << " consume " << result << endl;
            contadorConsumidor = (contadorConsumidor + 1) % BUFFER_CAPACITY;
            buffer_size--;
            return result;
        }

};

void productor(Buffer &buffer, int id){
    while(1){
        int new_int = rand() % 10 + 1;
        buffer.produce(id, new_int);
        this_thread::sleep_for(milliseconds(100));
    }   
}

void consumidor(Buffer &buffer, int id){
    while(1){
        this_thread::sleep_for(milliseconds(1000));
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

