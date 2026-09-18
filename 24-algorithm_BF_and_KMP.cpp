#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <string>
#include <numeric>
#include <functional>
using namespace std;

//  串操作实验代码 BF & KMP

ostream& operator<<(ostream& c, const vector<int>& vec) {
    for(int i = 0; i < (int)vec.size(); i++) {
        c << vec[i] << " ";
    }
    return c;
}

// 模板代码
// Q : 判断字符串 s 是否为 str 的字串 
bool BF_solute(string str, string s) { // BF 求解 暴力双指针
    int n = str.size();
    int m = s.size();
    if(n < m) return false;
    int i = 0, j = 0, k = 0;
    while(true) {
        if(n - i < m) return false;
        if(str[k] == s[j]) {
            k++;
            j++;
            if(j == m) return true;
        }
        else {
            j = 0;
            i++;
            k = i;
            continue;
        }
    }
    return false;
}
void test_BF_solute() {
    string str = "fahjfgafajkfkerw";
    string s = "gafa";
    cout << "主串:" << str << endl;
    cout << "目标字符串:" << s << endl;
    if(BF_solute(str, s)) {
        cout << "目标字符串在主串中存在" << endl;
    }
    else {
        cout << "目标字符串在主串中不存在" << endl;
    }
}

// next数组 next[i]表示子串第i个字符前面字符串的公共前后缀长度
// 例如 abcdabc的公共前后缀是abc，长度为3
vector<int> getNext(string s) { // 计算子串对应的next数组 next[0] == 0
    int n = s.size();
    vector<int> next(n);
    next[0] = 0;
    int j = 0;
    for(int i = 1; i < n; i++) {
        while(j > 0 && s[i] != s[j]) {
            j = next[j - 1];
        }
        if(s[i] == s[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}
vector<int> GetNext(string s) { // 计算字串对应的next数组 next[0] == -1
    int n = s.size();
    int j = 0, k = -1;
    vector<int> next(n);
    next[0] = -1;
    while(j < n - 1) {
         if(k == -1 || s[j] == s[k]) {
            k++;
            j++;
            next[j] = k;
        }
        if(s[k] == s[j]) {
            j++;
            k++;
            if(s[k] == s[j]) { // 求next数组的优化：若在k回退后s[i] == s[k] 则在回退
                next[j] = next[k];
            }
            else next[j] = k; 
        }
        else { // k回溯 
            k = next[k];
            j++;
        }
    }
    return next;
}
bool KMP_solute(string str, string s) {
    if(s.size() > str.size()) return false;
    int n = str.size(), m = s.size();
    vector<int> next = getNext(s);
    // int i = 0; // 指向主串的字符
    int j = 0; // 指向模式串的字符
    // int k = next[0]; // 第 j 个字符前面的公共前后缀长度
    for(int i = 0; i < n; i++) {
        while(j > 0 && str[i] != s[j]) {
            j = next[j - 1];
        }
        if(str[i] == s[j]) {
            j++;
        }
        if(j == m) return true;
    }
    return false;
}
void test_KMP_solute() {
    string str = "abcababc";
    string s = "abcabx";
    cout << "主串:" << str << endl;
    cout << "目标字符串:" << s << endl;
    if(KMP_solute(str, s)) {
        cout << "目标字符串在主串中存在" << endl;
    }
    else {
        cout << "目标字符串在主串中不存在" << endl;
    }
}

int main() {
    test_BF_solute();
    cout << "-------------------------------------------------------------\n";
    test_KMP_solute();
    cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";
}