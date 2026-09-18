#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;
//贪心算法实验代码

// T1.  部分背包问题
// Q.   有n个物品，重量{w1,w2,...,wn},价值{v1,v2,...,vn},背包最大承重量为C,每个物品可选取部分，
//      价值和重量按比例计算。求最大价值
double Knapsack(vector<int>& weight, vector<int>& val, int cap) { // 部分背包问题 贪心算法求解
    int n = weight.size();
    // 定义物品结构体
    struct product{ 
        int id;
        int w;
        int v;
        double getPrice()const {
            return v * 1.0 / w;
        }
        bool operator>(const product& p)const {
            return getPrice() > p.getPrice();
        }
    };
    vector<product> pro(n);
    for(int i = 0; i < n; i++) {
        pro[i].id = i;
        pro[i].w = weight[i];
        pro[i].v = val[i];
    }
    sort(pro.begin(), pro.end(), [](const product& p1, const product& p2)->bool  {return p1 > p2;}); // 按 val / weight 降序排列
    double bestv = 0;//记录背包最大价值
    double c = cap;
    for(int i = 0; i < n; i++) {
        if(pro[i].w <= c) {
            c -= pro[i].w;
            bestv += pro[i].v;
        }
        else {
            bestv += pro[i].v * c / pro[i].w;
            c = 0;
            break;
        }
        if(c == 0) break;
    }
    return bestv;
}
void test_Knspsack() {
    vector<int> weight = {5, 8, 3};
    vector<int> val = {10, 15, 9};
    int cap = 10;
    cout << "物品的重量:";
    for(int w : weight) cout << w << " ";
    cout << endl;
    cout << "物品的价值:";
    for(int v : val) cout << v << " ";
    cout << endl;
    cout << "背包初始容量:" << cap << endl;
    cout << "背包的最大价值:" << Knapsack(weight, val, cap) << endl;
}

// T2. 硬币选择问题
// ps: 贪心算法求解硬币选择问题需要硬币面值满足贪心性质 每个面额都接近前一个面额的2倍 否则不是最优解
int coinSelect(vector<int>& coins, int target) {
    int n = coins.size();
    sort(coins.begin(), coins.end(), greater<int>());
    int cnt = 0;
    int t = target;
    int idx = 0;
    while(t && idx < n) {
        if(coins[idx] <= t) {
            t -= coins[idx];
            cnt++;
        }
        else {
            idx++;
        }
        if(!t || idx >= n) break;
    }
    if(t) return -1;
    else return cnt;
}
void test_coinSelect() {
    vector<int> coins{1, 3, 5};
    int cnt = 11;
    cout << "硬币的面值:";
    for(int coin : coins) {
        cout << coin << " ";
    }
    cout << endl;
    cout << "要组成的目标值:" << cnt << endl;
    cout << "最少需要" << coinSelect(coins, cnt) << "枚硬币" << endl;
}

// T3. 柜台提供服务问题
// Q : m个柜台提供服务，每个柜台提供服务的时间是t，如何排列使得给所有用户提供服务的时间最少
int service(vector<int>& times, int num) { // 柜台服务问题 贪心算法求解
    int n = times.size();
    sort(times.begin(), times.end());
    struct Counter{ // 柜台
        int id;    //柜台编号
        int time; // 时间
        bool operator<(const Counter& c)const {
            return c.time < time;
        }
    };
    vector<Counter> cnts(n);
    for(int i = 0; i < n; i++) {
        cnts[i].id = i;
        cnts[i].time = times[i];
    }
    int ans = 0; // 记录最少时间
    vector<int> x(num);    // 记录每一个柜台安排的用户数量
    for(int i = 0; i < num; i++) {
        int time = cnts[0].time * (x[0] + 1); // 先计算把用户放在0号柜台的时间
        bool flag = true;
        for(int j = 1; j < n; j++) {
            int t = cnts[j].time * (x[j] + 1);
            if(t <= time) { // 放在其他柜台处理速度更快
                x[j]++;
                if(x[j] * cnts[j].time > ans) { // 新添加一个人使时间更长
                    ans = x[j] * cnts[j].time;
                }
                flag = false;
                break;
            }
        }
        if(flag) { // 最终还是在0号柜台时间更少
            x[0]++;
            ans = cnts[0].time * x[0];
        }
    }
    return ans;
}
void test_service() {
    vector<int>times = {3, 4, 100};
    cout << "个柜台的效率:";
    for(int x : times) {
        cout << x <<" ";
    }
    cout << endl;
    int num = 6;
    cout << "用户数量:" << num << endl;
    cout << "最少花费的时间:" << service(times, num) << endl;
}

int main() {
    test_Knspsack();
    cout << "-------------------------------------------------------------\n";
    test_coinSelect();
    cout << "-------------------------------------------------------------\n";
    test_service();
    cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";
}

//笔记最少的一集?