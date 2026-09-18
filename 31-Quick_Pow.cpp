#include <iostream>
#include <chrono>
using namespace std;
const int mod = 1000000007;
// 幂相关算法

int Nor_pow(int x, int y) { // 普通求幂
    int res = 1;
    for(int i = 0; i < y; i++) {
        res = (res * x) % mod;
    }
    return res;
}

// 3^10 = (3 * 3)^5 = 9 * (9 * 9)^2 = 9 * (81 * 81)
int quick_pow(int x, int y) { // 快速幂
    int res = 1;
    while(y) {
        if(y & 1) {
            res = (1LL * res * x) % mod;
        }
        x = (1LL * x * x) % mod;
        y >>= 1;
    }
    return res;
}

int main() {
    int x = 2, y = 1000000000;
    auto start = chrono::high_resolution_clock::now();
    cout << "普通求幂" << Nor_pow(x, y) << endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "函数执行耗时: " << duration.count() << " 微秒" << endl;

    auto start1 = chrono::high_resolution_clock::now();
    cout << "快速幂  " << quick_pow(x, y) << endl;
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1);
    cout << "函数执行耗时: " << duration1.count() << " 微秒" << endl;
}