#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <mutex>
#include <semaphore.h>

#define CANT_THREADS 10
#define MSG_COUNT 5
using namespace std;

int cont_a = 0;
int cont_b = 0;
//sem_t a(MSG_COUNT * 2);
//sem_t b(0);
sem_t a;
sem_t b;
sem_init(&a);   
sem_init(&b);

void f1_a(){
    for(int i = 0; i < MSG_COUNT; i++){
        sem_wait(a);
        cout << "Ejecutando F1 (A)\n";
        this_thread::sleep_for(100ms);
        cont_a++;
        if(cont_a == MSG_COUNT * 2) {
            b.signal(MSG_COUNT*2);
        }
        sem_post(a);
    }
}

void f1_b(){
    for(int i = 0; i < MSG_COUNT; i++){
        b.wait();
        cout << "Ejecutando F1 (b)\n";
        this_thread::sleep_for(200ms);
        cont_b++;
        b.signal();
    }
}

void f2_a(){
    for(int i = 0; i < MSG_COUNT; i++){
        a.wait();
        cout << "Ejecutando F2 (A)\n";
        this_thread::sleep_for(500ms);
        cont_a++;
        if(cont_a == MSG_COUNT * 2) {
            b.signal(MSG_COUNT*2);
        }
        a.signal();
    }
}

void f2_b(){
    for(int i = 0; i < MSG_COUNT; i++){
        b.wait();
        cout << "Ejecutando F2 (B)\n";
        this_thread::sleep_for(10ms);
        cont_b++;
        b.signal();
    }

   
}

void f1(){
    f1_a();
    f1_b();
}

void f2(){
    f2_a();
    f2_b();
}

int main(){

    thread t1 = thread(f1);
    thread t2 = thread(f2);
    t1.join();
    t2.join();

    return 0;

}

// binary_semaphore en caso de contar con una versión actulizada de GCC. Caso contrario usar sem_t