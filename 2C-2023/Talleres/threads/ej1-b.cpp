#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>

#define CANT_THREADS 10

using namespace std;

void f() {
    this_thread::sleep_for(500ms);
    cout << "Hola soy un thread" << endl;
}

int main() {
    vector<thread> v;
    for(int i = 0; i < CANT_THREADS; i++) {
        v.emplace_back(thread(f));
    }

    for(auto &t: v) {
        t.join();
        //t.detach();
    }
    return 0;
}
