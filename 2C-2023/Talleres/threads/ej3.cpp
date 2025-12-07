#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <mutex>
#include <assert.h>

#define N 100
#define THREAD_COUNT 5

using namespace std;

mutex m;

void verify(
    vector<int> v1, vector<int> v2, vector<int> v3) {
    cout << "v1 = [" << v1[0] << ", " << v1[1] << ", " << ", ..., " << v1[N - 2] << ", " << v1[N - 1] << "]" << endl;
    cout << "v2 = [" << v2[0] << ", " << v2[1] << ", " << ", ..., " << v2[N - 2] << ", " << v2[N - 1] << "]" << endl;
    cout << "v3 = [" << v3[0] << ", " << v3[1] << ", " << ", ..., " << v3[N - 2] << ", " << v3[N - 1] << "]" << endl;

    for (int i = 0; i < N; ++i) {
        assert(v3[i] == v1[i] * v2[i]);
    }
}

void f(
    vector<int>::iterator v1_begin,
    vector<int>::iterator v1_end,
    vector<int>::iterator v2_begin,
    vector<int>::iterator v2_end,
    vector<int>::iterator v3_begin,
    vector<int>::iterator v3_end,
){

    while(v1_begin != v1_end) {
        v3_begin.operator[]
    }
}

int main() {
    vector<int> v1(N);
    vector<int> v2(N);
    iota(v1.begin(), v1.end(), 1);
    iota(v2.begin(), v2.end(), N + 1);

    vector<int> v3(N);
    vector<thread> threads;

    for(int i = 0; i < THREAD_COUNT; i++){
        int step = N / THREAD_COUNT;
        int inicio = i*step;
        int final = step+inicio;
        threads.emplace_back(f, 
            v1.begin()+inicio, v1.begin()+final,
            v2.begin()+inicio, v2.begin()+final,
            v3.begin()+inicio, v3.begin()+final
            );
    }

    for(auto &t: threads) {
        t.join();
    }

    verify(v1, v2, v3);

    return 0;
}