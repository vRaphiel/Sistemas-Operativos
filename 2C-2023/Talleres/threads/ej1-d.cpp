#include <thread>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <vector>

#define CANT_THREADS 10

using namespace std;
mutex m;

void f() {
    for(int i = 0; i < 5; i++){
        lock_guard<mutex> lk(m);
        cout << "Hola! " << "Soy el thread " << i << endl;
        this_thread::sleep_for(500ms);
        cout << "Chau! " << "Soy el thread " << i << endl;
    }
}

int main() {
    vector<thread> threads;
    for(int i = 0; i < CANT_THREADS; i++) {
        threads.emplace_back(thread(f, &i));
    }
    for(auto &t: threads) {
        t.join();
        //t.detach();
    }
    sleep(1);
    return 0;
}
