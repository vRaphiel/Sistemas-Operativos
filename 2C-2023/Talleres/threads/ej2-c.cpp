#include <thread>
#include <iostream>
#include <semaphore.h>
#include <mutex>

using namespace std;

#define MSG_COUNT 10

mutex m;
int counter = 2;

void f1_a() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F1 (A)\n";
        this_thread::sleep_for(100ms);
    }

}
void f1_b() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F1 (B)\n";
        this_thread::sleep_for(200ms);
    }
}

void f2_a() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F2 (A)\n";
        this_thread::sleep_for(500ms);
    }
}

void f2_b() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F2 (B)\n";
        this_thread::sleep_for(10ms);
    }
}

void f1(sem_t &s, int &counter) {
    m.lock();
    f1_a();
    if(counter == 0) {
        sem_post(&s);
    } else {
        counter--;
    }
    m.unlock();
    sem_wait(&s);
    m.lock();
    f1_b();
    m.unlock();
}

void f2(sem_t &s, int &counter) {
    m.lock();
    f2_a();
    if(counter == 0) {
        sem_post(&s);
    } else {
        counter--;
    }
    m.unlock();
    sem_wait(&s);
    m.lock();
    f2_b();
    m.unlock();
}

int main() {
    sem_t sem_s;
    sem_init(&sem_s, 0, 0);

    thread t1(f1, ref(sem_s), ref(counter));
    thread t2(f2, ref(sem_s), ref(counter));

    t1.join();
    t2.join();
    sem_destroy(&sem_s);

    return 0;
}

/*
// WQORKS

main() {
    sem_init(&sem1,0,0);
    sem_init(&sem2,0,0);
}
void f1_aux() {
    f1_a();
    sem_post(&sem2);
    sem_wait(&sem1);
    f1_b();
}

void fb_aux() {
    f1_a();
    sem_post(&sem1);
    sem_wait(&sem2);
    f1_b();
}
*/