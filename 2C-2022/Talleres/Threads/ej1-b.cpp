#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>

#define CANT_THREADS 10
using namespace std;

void f() {
    this_thread::sleep_for(500ms);
    cout << "Hola" << endl;
}

void ejecutar(thread &t){
    this_thread::sleep_for(500ms);
}

int main(){
    // lanzamos un thread
    //vector<thread> thread_arr[CANT_THREADS];
    for(int i = 0; i  < CANT_THREADS; i++){
        //thread_arr[i] = thread(f);
        thread t = thread(f);
        //t.join(); // Wait
        t.detach();
        //sleep(1);
    }
    sleep(1);
    return 0;

    /**
    vector<thread> threads;
    for(int i = 0; i < CANT_THREADS; i++){
        threads.emplace_back();
    }
    for(int i = 0; i < CANT_THREADS; i++){
        threads[i].join();
        threads[i].detach();
    }    
    */
}