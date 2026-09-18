#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
// 回溯算法实验代码
using namespace std;
void func(int arr[], int i, int len) {//回溯递归 基础代码
    if(i == len) {//递归结束条件
        for(int j = 0; j < len; j++) {
            cout << arr[j] << " ";
        }
        cout << endl;
        return;
    }
    func(arr, i + 1, len);
    func(arr, i + 1, len);
}

// T1. 子集
void func2(int arr[], int i, int len, int x[]) {//回溯递归求子集
    //子集树模板代码
    if(i == len) {
        for(int j = 0; j < len; j++) {
            if(x[j] == 1){
                cout << arr[j] << " ";
            }
        }
        cout << endl;
        return;
    }
    //添加辅助数组 x[],仅选取x[i] == 1 的进行打印
    x[i] = 1;
    func2(arr, i + 1, len, x);
    x[i] = 0;
    func2(arr, i + 1, len, x);
}
void test_fun2(){
    int arr[] = {1, 2, 3};
    int len = sizeof(arr) / sizeof(arr[0]);
    //func(arr, 0, len);
    int x[3];
    func2(arr, 0, len, x);
}
int Min = INT_MAX;

// T2. 整数选取
void func3(int arr[], int i, int len, int x[]){//回溯算法--整数选取问题求解
    if(i == len) {
        int in = 0;
        int out = 0;
        for(int j = 0; j < len; j++) {
            if(x[j]) in += arr[j];
            else out += arr[j];
        }
        Min = min(Min, abs(in - out));
        return;
    }
    x[i] = 1;
    func3(arr, i + 1, len, x);//选择
    x[i] = 0;
    func3(arr, i + 1, len, x);//不选择
}
void test_fun3(){
    int arr1[] = {12, 6, 7, 11, 16, 3, 9};
    const int len1 = sizeof(arr1) / sizeof(int);
    int x1[len1] = {0};
    func3(arr1, 0, len1, x1);
    cout << Min << endl;
    Min = INT_MAX;
}
//全局变量
vector<int>bestx;//最优解
int in_sum = 0;//被选取部分的和
int out_sum = 0;//未被选取部分的和
int cnt = 0;
// T3. 2n整数问题
void func4(int arr[], int i, int len, vector<int>& x){//回溯算法求解 2n整数问题
    if(Min == 0) return;//优化3: 若Min为0，则已得到最优解，无需继续搜索
    if(i == len) {//得到子集树的一个解
        cnt++;
        if((int)x.size() != len / 2) {
            return;
        }
        if(Min > abs(in_sum - out_sum)) {
            Min = abs(in_sum - out_sum);
            bestx = x;
        }
        return;
    }
    if((int)x.size() < len){//剪枝优化1: 仅在还未选够 len/2 个整数时向左选取
        in_sum += arr[i];
        out_sum -= arr[i];
        x.push_back(arr[i]);
        func4(arr, i + 1, len, x);
        in_sum -= arr[i];
        out_sum += arr[i];
    }
    x.pop_back();
    if((int)x.size() + len - i - 1 >= len / 2){//剪枝优化2: 仅在可能选够 len/2 个整数时向右选取
        func4(arr, i + 1, len, x);
    }
}
int best = 0;
void test_fun4(){
    int arr[] = {12, 6, 7, 11, 16, 3, 9, 10};
    for(int x : arr) {
        out_sum += x;
    }
    const int len = sizeof(arr) / sizeof(int);
    vector<int>x;
    func4(arr, 0, len, x);
    cout << "Min = " << Min << endl;
    cout << "bestx:";
    for(int v : bestx) {
        cout << v <<' ';
    }
    cout << endl;
    //cout << cnt << endl;
    Min = INT_MAX; in_sum = 0; out_sum = 0; bestx.clear();//重置全局变量
}

// T4. 挑数字问题
vector<vector<int>>ans;
void func5(int arr[], int i, int len, int x[], int sum){//挑数字问题，回溯算法求解 子集树模板
    if(i == len) {
        int sum_in = 0;
        vector<int>res;
        for(int j = 0; j < len; j++) {
            if(x[j] == 1){
                sum_in += arr[j];
                res.push_back(arr[j]);
            }
        }
        if(sum_in == sum) {
            ans.push_back(res);
        }
        return;
    }
    x[i] = 1;
    func5(arr, i + 1, len, x, sum);
    x[i] = 0;
    func5(arr, i + 1, len, x, sum);
}
void test_fun5(){
    int arr[] = {12, 6, 7, 11, 16, 3, 9, 10};
    sort(arr, arr + 7);
    const int len = sizeof(arr) / sizeof(int);
    int x[len] = {};
    int sum;
    sum = 34;
    // cout << "输入子序列的和:";
    // cin >> sum;
    func5(arr, 0, len, x, sum);
    int c = 1;
    
    if(ans.empty() || ans[0].empty()) {
        cout << "不存在和为" << sum <<"的子序列" << endl;
        return;
    }
    cout << "和为" << sum << "的子序列如下" << endl;
    for(auto& res : ans) {
        cout << "第" << c++ <<"组: ";
        for(int i : res) {
            cout << i << " ";
        }
        cout << endl;
    }
    ans.clear();//全局变量重置
    return;
}
// vector<vector<int>> ans;
//int in_sum = 0; 使用的全局变量
void func6(vector<int>& arr, int i, int len, vector<int>& x, int target){//挑数字问题，剪枝优化版
    if(i == len) {
        if(in_sum == target) {
            ans.push_back(x);
        }
        return;
    }
    if(in_sum <= target) {//剪枝1 仅在当前选取的数字和小于等于目标值时继续向左搜索
        in_sum += arr[i];
        x.push_back(arr[i]);
        func6(arr, i + 1, len, x, target);
        in_sum -= arr[i];
        x.pop_back();
    }
    if(in_sum + accumulate(arr.begin() + i + 1, arr.end(), 0) >= target){
        //剪枝2 仅在当前选取的数字和 + 剩余可选的数字的和大于或等于目标值时，继续向右搜索
        func6(arr, i + 1, len, x, target);
    }
    return;
}
void test_fun6(){
    vector<int>arr = {12, 6, 7, 11, 16, 3, 9, 10};
    int len = arr.size();
    vector<int>x;
    int sum;
    sum = 41;
    // sort(arr.begin(), arr.end());
    func6(arr, 0, len, x, sum);
        if(ans.empty() || ans[0].empty()) {
        cout << "不存在和为" << sum <<"的子序列" << endl;
        ans.clear();
        return;
    }
    cout << "和为" << sum << "的子序列如下" << endl;
    int c = 1;
    for(auto& res : ans) {
        cout << "第" << c++ <<"组: ";
        for(int i : res) {
            cout << i << " ";
        }
        cout << endl;
    }
    ans.clear();in_sum = 0;//全局变量重置
    return;
}
//vector<vector<int>> ans; // 使用的全局变量
void func7(vector<int>& arr, int i, int len, vector<int>& x, int target) {//挑数字问题，更高效的回溯算法 穷举法
    //可抽象为 n叉树 n为递归的次数
    if(target == 0) {
        ans.push_back(x);
        return;
    }
    for(int k = i; k < len; k++) {
        //从当前结点开始，生成剩余的子节点
        if(target >= arr[k]) {//剪枝：仅当待组成的target大于arr[k]时生成子节点
            x.push_back(arr[k]);
            func7(arr, k + 1, len, x, target - arr[k]);
            //若允许重复，则变为
            //func7(arr, k, len, x, target - arr[k]);
            //即子节点包括自身
            x.pop_back();
        }
    }
}
void test_fun7(){
    vector<int> arr = {12, 6, 7, 11, 16, 3, 9, 10};
    vector<int> x;
    int len = arr.size();
    int target;
    target = 23;
    func7(arr, 0, len, x, target);
    if(ans.empty() || ans[0].empty()) {
        cout << "不存在和为" << target <<"的子序列" << endl;
        ans.clear();
        return;
    }
    int c = 1;
    cout << "和为" << target << "的子序列如下" << endl;
    for(auto& v : ans) {
        cout << "第" << c++ << "组: ";
        for(int a : v) {
            cout << a << " ";
        }
        cout << endl;
    }
    ans.clear();//全局变量重置
}

int Max = INT_MIN;
int sumout;
vector<vector<int>>best_v;
// T5. 01背包问题
/*
    Q : 一组物品 重量{w1, w2, w3 ... wn}
                价值{v1, v2, v3, ... vn} 
    背包最大承重量为M 求可以装下的物品的最大总价值
*/
void func8(vector<int>& weight, vector<int>& value, int i, int len, vector<int>& x, int w_sum, int v_sum, int cap) { //01背包问题，回溯递归求解
    if(i == len) {
        if(w_sum <= cap && v_sum >= Max) {
            if(Max == v_sum) {
                best_v.push_back(x);
            }
            else {
                Max = v_sum;
                best_v = {x};
            }
        }
        return;
    }
    sumout -= value[i];
    if(w_sum + weight[i] <= cap){//剪枝1 ：仅在添加后背包内物品不超过背包容量时向左搜索
        x.push_back(value[i]);
        v_sum += value[i];
        w_sum += weight[i];
        func8(weight, value, i + 1, len, x, w_sum, v_sum, cap);
        x.pop_back();
        v_sum -= value[i];
        w_sum -= weight[i];
    }
    sumout += value[i];
    if(Max < sumout){ //剪枝2 : 仅在剩余可选元素的价值和大于当前最优解时继续向右搜索
        func8(weight, value, i + 1, len, x, w_sum, v_sum, cap);
    }
}
void test_fun8() {
    Max = INT_MIN;best_v.clear();//全局变量重置
    vector<int> weight = {12, 5, 8, 9, 6};
    vector<int> value = {9, 11, 4, 7, 8};
    sumout = accumulate(value.begin(), value.end(), 0);
    int len = weight.size();
    vector<int> x;
    int cap = 20;
    // cin >> cap;
    func8(weight, value, 0, len, x, 0, 0, cap);
    cout << "最大价值为:";
    cout << Max << endl;
    cout << "选取元素的价值分别为:";
    //int c = 1;
    for(auto best : best_v) {
        for(auto bt : best) {
            cout << bt << " ";
        }
        cout << endl;
    }
} 

//vector<vector<int>>ans; 使用的全局变量
//vector<vector<int>>ans;
// T6. 全排列
void func9(vector<int>& arr, int i, int len){ // 全排列 排列树模板代码
    if(i == len) {
        ans.push_back(arr);
        return;
    }
    for(int k = i; k < len; k++) {
        swap(arr[i], arr[k]);
        func9(arr, i + 1, len);
        swap(arr[i], arr[k]);
    }
}
void test_fun9() {
        ans.clear();//重置全局变量
    vector<int>arr = {1, 2, 3};
    for(int temp : arr)cout << temp << " ";
    cout << "的全排列如下\n";
    func9(arr, 0, arr.size());
    for(auto &v : ans) {
        for(int a : v) {
            cout << a << " ";
        }
        cout << endl;
    }
}
void func10(vector<int>& arr, int i, int len, vector<int>&x, vector<bool>& state) { //全排列 穷举法求解
    if(i == len) {
        ans.push_back(x);
        return;
    }
    for(int k = 0; k < len; k++) {
        //k 表示可选的起始位置；
        //i 表示递归的第几层
        if(!state[k]) {
            state[k] = true;
            x.push_back(arr[k]);
            func10(arr, i + 1, len, x, state);
            x.pop_back();
            state[k] = false;
        }
    }
}
void test_fun10(){
    ans.clear();//重置全局变量
    vector<int>arr = {1, 2, 3};
    for(int temp : arr)cout << temp << " ";
    cout << "的全排列如下\n";
    vector<int> x;
    vector<bool> state(arr.size(), false);
    func10(arr, 0, arr.size(), x, state);
    for(auto &v : ans) {
        for(int a : v) {
            cout << a << " ";
        }
        cout << endl;
    }
}

// T7. N皇后问题
bool judge(vector<int>& arr, int i) { //判断是否满足8皇后的排列规则
    for(int j = 0; j < i; j++) {
        if(i == j || arr[i] == arr[j] || abs(i - j) == abs(arr[i] - arr[j]))return false;//在同一 行/列/斜线 上有不止一个皇后
    }
    return true;
}
int cnt_q = 0;//统计排列次数
void func11(vector<int>& arr, int i, int len){ //N皇后问题 回溯求解 （排列树）
    /*Q ：8行8列棋盘 8个皇后 任意两个皇后之间不能处于同一行，同一列，同一斜线上，怎么摆放，多少种摆法*/
    if(i == len) {
        cnt_q++;
        for(int j = 0; j < len; j++) {
            cout << arr[j] << " ";
        }
        cout << endl;
        return;
    }

    for(int k = i; k < len; k++) {
        swap(arr[i], arr[k]);
        if(judge(arr, i)) {
            func11(arr, i + 1, len);
        }
        swap(arr[i], arr[k]);
    }
}
void test_fun11(){
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};//arr的下标作为纵坐标，arr的值作为横坐标
    int len = arr.size();
    func11(arr, 0, len);
    cout << cnt_q << endl;
    cnt_q = 0;
}

int main(){
    test_fun2();
    cout << "-------------------------------------------------------------\n";
    test_fun3();
    cout << "-------------------------------------------------------------\n";
    test_fun4();
    cout << "-------------------------------------------------------------\n";
    test_fun5();
    cout << "-------------------------------------------------------------\n";
    test_fun6();
    cout << "-------------------------------------------------------------\n";
    test_fun7();
    cout << "-------------------------------------------------------------\n";
    test_fun8();
    cout << "-------------------------------------------------------------\n";
    test_fun9();
    cout << "-------------------------------------------------------------\n";
    test_fun10();
    cout << "-------------------------------------------------------------\n";
    test_fun11();
    cout << "-------------------------------------------------------------\n";
    return 0;
}

//两面包夹芝士
//{12, 6, 7, 11, 16, 3, 9, 10}.
// std::cout << __cplusplus << std::endl;
