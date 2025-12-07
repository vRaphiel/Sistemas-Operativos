#include <thread>
#include <iostream>
#include <unistd.h>

#define CANT_THREADS 10

using namespace std;

void f(int* i, string s) {
    this_thread::sleep_for(500ms);
    printf("%s %i\n", s.c_str(), *i);
}

int main() {
    for(int i = 0; i < CANT_THREADS; i++) {
        thread* t = new thread(f, &i, "Hola! Soy el thread:");
        t->join();
    }
    sleep(1);
    return 0;
}
