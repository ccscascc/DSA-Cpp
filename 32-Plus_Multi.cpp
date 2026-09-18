#include <iostream>
using namespace std;

// 位运算加法，乘法（即二进制加法，乘法）
// 思路即模拟竖式计算的方法

int Plus(int a, int b) { // 位运算加法(二进制加法)
    while(b) {
        int x = (a ^ b); // 不考虑进位的和（1+1=0）可以用异或表示
        int y = (a & b); // 每一位相加产生的进位（1+1=0，进1）可以用与表示
        a = x; // 将不考虑进位的和作为一个新的加数
        b = (y << 1); // 将每一位产生的进位左移一位作为另一个新的加数
    }
    return a;
}

int Multiply(int a, int b) { // 位运算乘法(二进制乘法)
    int res = 0; // 初始为0
    while(b) {
        if(b & 1) {
            res = Plus(res, a); 
        }
        b >>= 1;
        a <<= 1;
    }
     return res;
}

int main() {
    int a = 10, b = 23;
    cout << a << '+' << b << '=' << Plus(a, b) << endl;
    cout << a << '*' << b << '=' << Multiply(a, b) << endl;
    cout << ~3;
}