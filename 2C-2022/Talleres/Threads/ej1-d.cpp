#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <mutex>

#define CANT_THREADS 10
using namespace std;

mutex mtx;

//void f(int i) {
//    for(int i = 0; i < 5; i++){
//        mtx.lock();
//        cout << "Hola! Soy el thread: " << i << endl;
//        this_thread::sleep_for(100ms);
//        cout << "Chau! Saludos desde: " << i << endl;
//        mtx.unlock();
//        return;
//    }
//}

void f(int i) {

        lock_guard <mutex> lk(mtx);
        cout << "Hola! Soy el thread: " << i << endl;
        this_thread::sleep_for(100ms);
        cout << "Chau! Saludos desde: " << i << endl;
        return;

}

//void f(int i) {
//    cout << "Hola! Soy el thread: " << i << endl;
//    this_thread::sleep_for(100ms);
//    cout << "Chau! Saludos desde: " << i << endl;
//}

int main(){
    // lanzamos un thread
    //vector<thread> thread_arr[CANT_THREADS];
    //for(int i = 0; i  < CANT_THREADS; i++){
        //thread_arr[i] = thread(f);
    //    thread t = thread(f, i);
        //t.detach();
        //sleep(1);
    //    t.join(); // Wait
    //}
    //sleep(1);
    //return 0;

    vector<thread> threads;

    for(int i = 0; i < CANT_THREADS; i++){
        threads.emplace_back(thread(f, i));
    }
    for(int i = 0; i < CANT_THREADS; i++){
        threads[i].join();
        //threads[i]. detach();
    }

    return 0;

}