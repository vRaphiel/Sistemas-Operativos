#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <mutex>
#include <semaphore.h>
#include <numeric>
#include <atomic>

#define N 100

using namespace std;
mutex mtx;

void f(vector<int> &v1, vector<int> &v2, atomic<int> &acumulador, atomic<int> &indice, int i, vector<int> &operaciones) {
    int local;
    while((local = indice++) < 100){
        acumulador += (v1[local] * v2[local]);
        operaciones[i] += 1;
        this_thread::sleep_for(5ms*(i + 1));
    }
}

int main(){
    atomic<int> indice{0};
    int current_thread = 0;
    vector<thread> t_arr;

    vector<int> operaciones(5, 0);
    vector<int> v1(N);
    vector<int> v2(N);

    atomic<int> res{0};
    int val = 20;

    iota(v1.begin(), v1.end(), 1);
    iota(v2.begin(), v2.end(), N + 1);

    for(int i = 0; i < 5; i++){
        t_arr.emplace_back(f, ref(v1), ref(v2), ref(res), ref(indice), i, ref(operaciones));
    }

    for(int i = 0; i < 5; i++){
        t_arr[i].join();
    }

    cout << res << endl;
    
    return 0;
}