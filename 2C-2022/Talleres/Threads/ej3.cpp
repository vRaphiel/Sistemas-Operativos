#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <mutex>
#include <semaphore.h>
#include <numeric>

#define N 100

using namespace std;

void f(vector<int> &v1, vector<int> &v2, vector<int> &v3, int valor) {
    for(int i = valor; i < valor + 20; i++){
        v3[i] = v1[i] * v2[i];
    }
    return;
}

int main(){
    vector<thread> t_arr;
    vector<int> v1(N);
    vector<int> v2(N);
    vector<int> v3(N);
    int val = 20;
    iota(v1.begin(), v1.end(), 1);
    iota(v2.begin(), v2.end(), N + 1);

    for(int i = 0; i < 5; i++){
        int count = 20*i;
        t_arr.emplace_back(f, ref(v1), ref(v2), ref(v3), count);
    }

    for(int i = 0; i < 5; i++){
        t_arr[i].join();
    }

    for(int i = 0; i < N; i++){
        cout << v3[i] << endl;
    }
    return 0;
}

// binary_semaphore en caso de contar con una versión actulizada de GCC. Caso contrario usar sem_t