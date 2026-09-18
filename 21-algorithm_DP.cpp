#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <string>
#include <ctime>

using namespace std;

// 动态规划实验代码
vector<long long> DP;//全局dp数组

// T1. 硬币选择问题 
// Q.  给定不同面值硬币组成给定大小所需的最小硬币数量 硬币面值此处为 1，3，5
//     问题的状态 dp[n] 组成面值为n 所需的最少硬币数
//     状态转移方程 {dp[i] = min(dp[i], dp[i - val[j]] + 1); //dp[i]初始为i
int coin_select_1(int n) { // 硬币选择问题 动态规划求解 递归
    //利用dp数组进行记忆化存储，避免重复求解子问题
    if(DP[n] != 0) return DP[n];
    if(n == 1 || n == 3 || n == 5) {
        DP[n] = 1;
        return 1;
    }
    else if(n == 2 || n == 4) {
        DP[n] = 2;
        return 2;
    }
    else {
        int n1 = coin_select_1(n - 1) + 1;// 假设选取1分硬币
        int n2 = coin_select_1(n - 3) + 1;// 假设选取3分硬币
        int n3 = coin_select_1(n - 5) + 1;// 假设选取5分硬币
        DP[n] =  min({n1, n2, n3});
        return DP[n];
    }
}
void test_coin_select_1() {
    int val = 11;//所求的总面值
    DP.resize(val + 1);
    cout << "组成" << val << "最少需要" << coin_select_1(val) << "枚面值为1或3或5的硬币" << endl;
    DP.clear();
}
void coin_select_2(int n) {// 硬币选择问题 动态规划求解 非递归
    vector<int>dp;
    int val[] = {1, 3, 5};
    dp.resize(n + 1);
    for(int i = 0; i <= n; i++) {
        dp[i] = i;//.表示初始全部由面值为1的硬币组成
        for(int j = 0; j < sizeof(val) / sizeof(int); j++) {
            if(i >= val[j] && (1 + dp[i - val[j]]) < dp[i]) {
                dp[i] = 1 + dp[i - val[j]];
            }
        }
    }
    cout << "组成" << n << "最少需要" << dp[n] << "枚面值为1或3或5的硬币" << endl;
}
void test_coin_select_2() {
    int n = 32;
    coin_select_2(290);
}

// T2. 斐波那契数列
// 状态转移方程 dp[i] = dp[i - 1] + dp[i - 2]; dp[0] = 0; dp[1] = 1
int fabnacci_1(int n) {// 简单递归--(分治算法)
    if(n == 0) return 0;
    if(n == 1 || n == 2) return 1;
    return fabnacci_1(n - 1) + fabnacci_1(n - 2);
}
void test_fabnacci_1() {
    int n = 30;
    cout << "斐波那契数列第" << n << "项:" << fabnacci_1(n) << endl;
}
long long fabnacci_2(int n) {// 动态规划求解 递归
    if(DP[n] != 0) return DP[n];
    if(n == 0) return 0;
    DP[n] = fabnacci_2(n - 1) + fabnacci_2(n - 2);
    return DP[n];
}
void test_fabnacci_2() {
    int n;
    DP.clear();
    n = 70;
    DP.resize(n + 1);
    DP[0] = 0; DP[1] = 1;
    cout << "斐波那契数列第" << n << "项:" << fabnacci_2(n) << endl;
    DP.clear();
}
long long fabnacci_3(int n) { //动态规划求解 非递归
    vector<long long> dp(n + 1);
    if(n == 0) return 0;
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}
void test_fabnacci_3() {
    int n = 0;
    cout << "斐波那契数列第" << n << "项:" << fabnacci_3(n) << endl;
}

// T2. 最大子段和
/*  
    Q : 给定数组arr[n],求出和最大的子段(子数组) 动态规划
    dp[i] 为以下标i为结尾的子段和 dp[0] = max(0, dp[0]); dp[1] = dp[0] + arr[1];
    状态转移方程 dp[i] = arr[i] + max(0, dp[i - 1]);
*/
int test_max_subarray(vector<int>& nums) {
    int n = nums.size();
    int* dp = new int[n]();
    dp[0] = nums[0];
    int mx = dp[0];
    for(int i = 1; i < n; i++) {
        dp[i] = max(0, dp[i - 1]) + nums[i];
        mx = max(mx, dp[i]);
    }
    delete[] dp;
    return mx;
}
void test_max_subarray() {
    vector<int> nums;
    cout << "原数组元素:";
    for(int i = 0; i < 10; i++) {
        nums.push_back(rand() % 20 + 1);
        if(i % 3) nums[i] *= -1;
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << "最大子段和为:" << test_max_subarray(nums) << endl;
}

// T3. 最长非降子序列长度(LIS)
/*
    Q : 给定数组 nums[n],求出最长的非降序的子序列
    状态: dp[i]表示以第i个元素为结尾的最长非降子序列  dp[0] = 1;
    状态转移方程：dp[i] = nums[i] >= nums[j] ? dp[j] + 1 : 1;//(0 < i < n && 0 <= j < i)
*/
int LIS(vector<int>& nums) {
    int n = nums.size();
    if(nums.empty()) return 0;
    int* dp = new int[n]();
    int ans = dp[0];
    dp[0] = 1;
    for(int i = 1; i < n; i++) {
        dp[i] = 1;
        for(int j = 0; j < i; j++) {
            if(nums[i] >= nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}
void test_LIS() {
    vector<int> nums;
    cout << "原数组元素:";
    for(int i = 0; i < 10; i++) {
        nums.push_back(rand() % 20);
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << "最长非降子序列长度为:" << LIS(nums) << endl;
}

// T4. 最长公共子序列(LCS)
// Q1. 给定两个字符串 str1, str2，求出公共子序列长度
// 状态转移方程 dp[i][j] = str1[i] == str2[j] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i - 1][j]);
int LCS_DP_01(string str1, string str2, int** dp) { //LCS 动态规划求解 递归 二维DP数组
    int n = str1.size(), m = str2.size();
    if(str1.empty() || str2.empty()) return 0;
    if(dp[n - 1][m - 1] != -1) return dp[n - 1][m - 1];
    if(str1.back() == str2.back()) {
        dp[n - 1][m - 1] = LCS_DP_01(str1.substr(0, n - 1), str2.substr(0, m - 1), dp) + 1;
        return dp[n - 1][m - 1];
    }
    else {
        int len1 = LCS_DP_01(str1.substr(0, n - 1), str2.substr(0, m), dp);
        int len2 = LCS_DP_01(str1.substr(0, n), str2.substr(0, m - 1), dp);
        dp[n - 1][m - 1] = max(len1, len2);
    }
    return dp[n - 1][m - 1];
}
void test_LCS_DP_01() {
    string str1 = "helloworld";
    string str2 = "hlweord";
    int n = str1.size(), m = str2.size();
    cout << "字符串1:" << str1 << endl;
    cout << "字符串2:" << str2 << endl;
    int** dp = new int*[n]();
    for(int i = 0; i < n; i++) {
        dp[i] = new int[m]();
        fill(dp[i], dp[i] + m, -1);
        // for(int j = 0; j < m; j++) dp[i][j] = -1;
    }
    cout << "最长公共子序列长度:" << LCS_DP_01(str1, str2, dp) << endl;
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         if(dp[i][j] == -1) cout << '*' <<" ";
    //         else cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for(int i = 0; i < n; i++) {
        delete[] dp[i];
    }
    delete[] dp;
}
int LCS_DP_02(string str1, string str2) { //LCS 动态规划求解 非递归
    int n = str1.size(), m = str2.size();
    if(str1.empty() || str2.empty()) return 0;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    int ans = dp[0][0];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}
void test_LCS_DP_02() { 
    string str1 = "helloworld";
    string str2 = "hlweord";
    int n = str1.size(), m = str2.size();
    cout << "字符串1:" << str1 << endl;
    cout << "字符串2:" << str2 << endl;
    cout << "最长公共子序列长度:" << LCS_DP_02(str1, str2) << endl;
}
// Q2 : 求出str1,str2 的最长公共子序列
int LCS_DP_03(string str1, string str2, vector<vector<int>>& dp, vector<vector<int>>& path) { // 输出最长公共子序列 递归
    int n = str1.size(), m = str2.size();
    if(str1.empty() || str2.empty()) {
        return 0;
    }
    if(dp[n - 1][m - 1] != -1) {
        return dp[n - 1][m - 1];
    }
    else {
        if(str1[n - 1] == str2[m - 1]) {
            dp[n - 1][m - 1] = LCS_DP_03(str1.substr(0, n - 1), str2.substr(0, m - 1), dp, path) + 1;
            path[n - 1][m - 1] = 1; // 表示从 [n - 1][m - 1] -> [n - 2][m - 2] 对角线左上移动
            return dp[n - 1][m - 1];
        }
        else {
            int len1 = LCS_DP_03(str1.substr(0, n), str2.substr(0, m - 1), dp, path);
            int len2 = LCS_DP_03(str1.substr(0, n - 1), str2.substr(0, m), dp, path);
            if(len1 >= len2) {
                path[n - 1][m - 1] = 2;  // 表示从 [n - 1][m - 1] -> [n - 2][m - 1] 往上
            }
            else path[n - 1][m - 1] = 3; // 表示从 [n - 1][m - 1] -> [n - 1][m - 2] 往左
            dp[n - 1][m - 1] = max(len1, len2);
            return dp[n - 1][m - 1];
        }
    }
}
void backStrace(vector<vector<int>>& path, string str, int n, int m) { // 递归输出公共子序列
    if(n < 0 || m < 0) return;
    if(path[n][m] == 1) {
        backStrace(path, str, n - 1, m - 1);
        cout << str[n];
    }
    else if(path[n][m] == 2) backStrace(path, str, n, m - 1);
    else backStrace(path, str, n - 1, m);
}
void test_LCS_DP_03() {
    string str1 = "helloworld";
    string str2 = "hlweord";
    cout << "字符串1:" << str1 << endl;
    cout << "字符串2:" << str2 << endl;
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    vector<vector<int>> path(n, vector<int>(m, 0));
    LCS_DP_03(str1, str2, dp, path);
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         cout << path[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    string str;
    for(int i = n - 1; i >= 0; ) {
        for(int j = m - 1; j >= 0; ) {
            if(path[i][j] == 1) {
                str += str1[i];
                i--;
                j--;
            }
            else if(path[i][j] == 2) {
                j--;
            }
            else i--;
        }
    }
    reverse(str.begin(), str.end());
    cout << "最长公共子序列:" << str << endl;
    cout << "最长公共子序列:";
    backStrace(path, str1, n - 1, m - 1);
    cout << endl;
}
string LCS_DP_04(string str1, string str2) {//输出最长公共子序列 非递归
    int n = str1.size(), m = str2.size();
    int** dp = new int*[n + 1]();
    int** path = new int*[n + 1]();
    for(int i = 0; i <= n; i++) {
        dp[i] = new int[m + 1]();
        path[i] = new int[m + 1]();
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = 1;
            }
            else if(dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                path[i][j] = 3;
            }
            else {
                dp[i][j] = dp[i][j - 1];
                path[i][j] = 2;
            }
        }
    }
    string ans;
    for(int i = n; i > 0; ) {
        for(int j = m; j > 0; ) {
            if(path[i][j] == 1) {
                ans += str1[i - 1];
                i--;
                j--;
            }
            else if(path[i][j] == 2) {
                j--;
            }
            else i--;
        }
    }
    for(int i = 0; i < n; i++) {
        delete[] dp[i];
        delete[] path[i];
    }
    delete[] dp;
    delete[] path;
    reverse(ans.begin(), ans.end());
    return ans;
}
void test_LCS_DP_04() {
    string str1 = "helloworld";
    string str2 = "hlweord";
    int n = str1.size(), m = str2.size();
    cout << "字符串1:" << str1 << endl;
    cout << "字符串2:" << str2 << endl;
    cout << "最长公共子序列:" << LCS_DP_04(str1, str2) << endl;
}

// T5. 01背包问题
/*
    Q : 一组物品 重量{w1, w2, w3 ... wn}
    价值{v1, v2, v3, ... vn} 
    背包最大承重量为M 求可以装下的物品的最大总价值
    状态 : dp[i][j] 表示当背包剩余容量为 j 时容纳的最大价值 
    状态转移方程 : dp[i][j] = w[i] < j ? dp[i + 1][j] : max(dp[i + 1][j], val[i] + dp[i + 1][j - weight[i]]);
*/
vector<vector<int>> Knapsack01(vector<int>& weight, vector<int>& val, int cap) { // 01背包问题动态规划求解
    int n = weight.size();
    vector<vector<int>> dp(n, vector<int>(cap + 1));
    vector<vector<int>> ans;
    for(int j = 1; j <= cap; j++) { //对dp数组进行初始化
        if(weight[n - 1] > j) {
            dp[n - 1][j] = 0;
        }
        else {
            dp[n - 1][j] = val[n - 1];
        }
    }
    for(int i = n - 2; i >= 0; i--) { // i 表示所选的物品是第i个到第 n - 1 个
        for(int j = 1; j <= cap; j++) { // j 表示选取第 i 各物品时背包剩余容量
            if(j >= weight[i]) { // 放得下
                dp[i][j] = max(dp[i + 1][j], val[i] + dp[i + 1][j - weight[i]]);
            }
            else { // 放不下
                dp[i][j] = dp[i + 1][j];
            }
        }
    }
    int bestv = 0;
    for(int i = 0; i < n - 1; i++) {
        if(dp[i][cap] != dp[i + 1][cap]) { // 表示选择了第i个物品
            bestv += val[i];
            cap -= weight[i];
            ans.push_back({weight[i], val[i]});
        }
    }
    if(dp[n - 1][cap] > 0) {
        bestv +=val[n - 1];
        cap -= weight[n - 1];
        ans.push_back({weight[n - 1], val[n - 1]});
    }
    return ans;
}
void test_01_Knapsack() {
    vector<int> weight = {8, 6, 4, 2, 5};
    vector<int> val = {6, 4, 7, 8, 6};
    int cap = 11;   
    // vector<int> weight = {12, 5, 8, 9, 6};
    // vector<int> val = {9, 11, 4, 7, 8};
    // int cap = 20;
    cout << "物品的重量:";
    for(int w : weight) cout << w << " ";
    cout << endl;
    cout << "物品的价值:";
    for(int v : val) cout << v << " ";
    cout << endl;
    cout << "背包初始容量:" << cap << endl;
    int v = 0;
    vector<vector<int>> ans = Knapsack01(weight, val, cap);
for(auto vec : ans) {
        v += vec[1];
    }
    cout << "可以装下的最大价值:" << v << endl;
    
    cout << "所选物品的重量:";
    for(auto vec : ans) {
        cout << vec[0] << " ";
    }
    cout << endl;
    cout << "所选物品的价值:";
    for(auto vec : ans) {
        cout << vec[1] << " ";
    }
    cout << endl;
}

// T6. 三角数组求和
/*  
    Q : 一个三角形的数组，找出自顶向下的最小路径和
    状态转移方程 : dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + tri[i][j]
*/
int triangle_minsum(vector<vector<int>>& nums) {
    int n = nums.size();
    if(nums.empty()) return 0;
    if(nums.size() == 1) return nums[0][0];
    int m = nums[n - 1].size();
    vector<vector<int>> dp(n, vector<int>(n));
    int ans = INT_MAX;
    for(int i = 0; i < m; i++) {
        dp[n - 1][i] = nums[n - 1][i];
        ans = min(ans, dp[n - 1][i]);
    }
    for(int i = n - 2; i >= 0; i--) {
        for(int j = 0; j < nums[i].size(); j++) {
            dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + nums[i][j];
            ans = min(ans, dp[i][j]);
        }
    }
    return dp[0][0];
}
void test_triangle_minsum() {
    vector<int> nums1 = {2}, nums2 = {3, 4}, nums3 = {6, 5, 7}, nums4 = {4, 1, 8, 3};
    vector<vector<int>> tri = {nums1, nums2, nums3, nums4};
    cout << "三角数组:" << endl;
    for(auto nums : tri) {
        for(int num : nums) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << "最小路径和:" << triangle_minsum(tri) << endl;
}


int main() {
    test_coin_select_1(); 
    cout << "-------------------------------------------------------------\n";
    test_coin_select_2();
    cout << "-------------------------------------------------------------\n";
    test_fabnacci_1();
    cout << "-------------------------------------------------------------\n";
    test_fabnacci_2();
    cout << "-------------------------------------------------------------\n";
    test_fabnacci_3();
    cout << "-------------------------------------------------------------\n";
    test_max_subarray();
    cout << "-------------------------------------------------------------\n";
    test_LIS();
    cout << "-------------------------------------------------------------\n";
    test_LCS_DP_01();
    cout << "-------------------------------------------------------------\n";
    test_LCS_DP_02();
    cout << "-------------------------------------------------------------\n";
    test_LCS_DP_03();
    cout << "-------------------------------------------------------------\n";
    test_LCS_DP_04();
    cout << "-------------------------------------------------------------\n";
    test_01_Knapsack();
    cout << "-------------------------------------------------------------\n";
    test_triangle_minsum();
    cout << "-------------------------------------------------------------\n";
}
 

//落花人独立，微雨燕双飞