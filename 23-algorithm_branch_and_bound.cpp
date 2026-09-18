#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <queue>
#include <numeric>
#include <functional>
using namespace std;
// 分支限界算法代码

// T1. 集装箱装载问题
// Q : 一批n个集装箱要装上两艘载重量分别为 c1, c2 的轮船，集装箱的重量为{w1,w2,...,wn}
//     判断是否有办法把这些集装箱全部装上货轮
int bestw = 0; // 记录最优装载量
int cw = 0;    // 记录已被选的结点的质量之和 
struct Node{
    int weight; // 根节点到当前结点的总重量
    int level;  // 当前结点所在的层数
    Node* parent;  // 记录当前结点的父结点
    bool is_selected;// 记录当前结点是否被选择
    Node(int w = 0, int l = 0, Node* p = nullptr, int is = false) {
        weight = w;
        level = l;
        parent = p;
        is_selected = is;
    }
};
int rest = 0;
queue<Node*> que; // 广度优先遍历子集树的 FIFO 队列 // **FIFO队列 即先进先出的队列
Node* bestNode = nullptr;
int maxBound(vector<int>& weight, int level) { // 结点的上界函数，返回未被处理的物品总重量
    int s = 0;
    for(int j = level + 1; j >= 0; j--) {
        s += weight[j];
    }
    return s;
}
void addLiveNode(vector<int>& weight, int w, int level, Node* parent, bool is_selected) { // 添加活结点到queue中 即限界的过程
    int n = weight.size();
    Node *node = new Node(w, level, parent, is_selected);
    que.push(node);
    if(level == n && w == bestw) { // 在最后一层，记录最优解
        bestNode = node;
    }
}
bool containerLoading(vector<int>& weight, int c1, int c2) { // 集装箱装载问题  分支限界算法求解
    int n = weight.size();
    vector<int> res;
    int i = 0; // 起始层数
    Node* node = nullptr;
    while(i < n) { // 开始扩展node结点
        int wt = weight[i] + cw; // 处理左孩子  选择
        if(wt <= c1) {
            bestw = max(bestw, wt);
            // que.push(new Node(wt, i + 1)); 
            addLiveNode(weight, wt, i + 1, node, true);
        }
        rest = maxBound(weight, i);
        if(cw + rest >= bestw){ // 限界剪枝--
            // que.push(new Node(cw, i + 1)); // 处理右孩子 不选择
            addLiveNode(weight, cw, i + 1, node, false);
        }
        node = que.front();
        que.pop(); // 处理完所有子节点后，原结点成为死节点，出队
        // 更新i，cw 从i结点跳到广度遍历的下一个结点
        cw = node->weight;
        i = node->level; 
    }
    int tw = accumulate(weight.begin(), weight.end(), 0);
    if(bestNode == nullptr) return tw <= c2;
    vector<bool> bestx(n);
    for(int j = n - 1; j >= 0; j--) {
        bestx[j] = bestNode->is_selected;
        bestNode = bestNode->parent;
    }
    
    for(int j = 0; j < n; j++) {
        cout << bestx[j] << ' ';
        if(bestx[j]) tw -= weight[j];
    }
    cout << endl;
    return tw <= c2;
}
void test_containerLoading() {
    vector<int> weight = {6, 9 ,12};
    int c1 = 15, c2 = 12;
    if(containerLoading(weight, c1, c2)) {
        cout << "可以装下" << endl;
    }
    else cout << "不能装下" << endl;
}

// T2. 01背包问题
int bestv = 0; // 最优价值
int cw_;        // 当前背包的重量
int cv;        // 当前背包的价值
struct Node_ { // 物品结点
    int weight; //已选择物品的总重量
    int value;  //已选择物品的总价值
    int level;  //物品结点所在的层数
    bool is_selected; // 记录是否被选择
    Node_* parent;    // 父结点  
    Node_(int w, int v, int l, Node_* p, bool is) {
        weight = w;
        value = v;
        level = l;
        parent = p;
        is_selected = is;
    }
};
Node_* bestNode_ = nullptr; //记录最优解的叶子节点
queue<Node_*> que_; // 广度遍历
void addNode(vector<int>& weight, vector<int>& val, int w, int v, int level, Node_* parent, bool is_) {
    int n = weight.size();
    Node_* node = new Node_(w, v, level, parent, is_);
    que_.push(node);
    if(level == n && v == bestv) {
        bestNode_ = node;
    }
}
int maxBound_(vector<int>val, int i) { // 记录价值上界 即记录未处理的物品价值
    int n = val.size();
    int bound = 0;
    for(int lev = i + 1; lev < n; lev++) {
        bound += val[lev];
    }
    return bound;
}
int Knapsack01_FIFO(vector<int>& weight, vector<int>& val, int cap) { // FIFO队列
    int n = weight.size();
    int i = 0;
    Node_* node = nullptr;
    while(i < n) {
        int wt = weight[i] + cw_; // 当前的物品重量 + 已选物品重量 即处理左孩子，选择物品i
        if(wt <= cap) { // 限界：仅在已选的物品重量不超出背包承重时处理左子树
            bestv = max(bestv, cv + val[i]);
            addNode(weight, val, cw_ + weight[i], cv + val[i], i + 1, node, true);
        }
        int upBound = maxBound_(val, i);
        
        // 处理右孩子，不选择物品i
        if(cv + upBound >= bestv) { // 限界：仅在剩余未处理物品的总价值大于等于当前bestv 时才继续处理右子树
            addNode(weight, val, cw_, cv, i + 1, node, false);
        }
        node = que_.front();
        que_.pop();
        i = node->level;
        cv = node->value;
        cw_ = node->weight; // 更新i, cw, cv
    }
    return bestv;
}
int test_Knapsack01_FIFO() {
    vector<int> weight = {16, 15, 15};
    vector<int> value = {45, 25, 25};
    int n = weight.size();
    int cap = 45;
    cout << "物品的重量:";
    for(int w : weight) cout << w << ' '; cout << endl;
    cout << "物品的价值:";
    for(int v : value) cout << v << ' '; cout << endl;
    cout << "背包的承重:" << cap << endl;
    cout << "装下的最大价值为:" << Knapsack01_FIFO(weight, value, cap) << endl;
    cw = 0; cv = 0; bestv = 0; cw_ = 0;
    bool* sel = new bool[n]();
    for(int j = n - 1; j >= 0; j--) {
        sel[j] = bestNode_->is_selected;
        bestNode_ = bestNode_->parent;
    }
    for(int i = 0; i < n; i++) cout << sel[i] <<' ';
    cout << endl;
    while(!que.empty()) {
        que.pop();
    }
    delete[] sel;
}
struct NODE {
    int weight; //已选择物品的总重量
    int value;  //已选择物品的总价值
    int level;  //物品结点所在的层数
    bool is_selected; // 记录是否被选择
    NODE* parent;    // 父结点  
    int upbound;     // 结点的价值上界，即从这个节点往下最多可选择的物品产生的总价值
    NODE(int w, int v, int l, NODE* p, bool is, int up) {
        weight = w;
        value = v;
        level = l;
        parent = p;
        is_selected = is;
        upbound = up;
    }
};
priority_queue<NODE*, vector<NODE*>, function<bool(NODE*, NODE*)>> prque([](NODE* n1, NODE* n2)->bool {
    return n1->upbound < n2->upbound;
});
int maxbound(vector<int>& val, int i) {
    int bound = 0;
    int n = val.size();
    for(int l = i; l < n; l++) {
        bound += val[l];
    }
    return bound;
}
void addLiveNODE(vector<int>& weight, int w, int v, int level, NODE* parent, bool is, int upb) {
    int n = weight.size();
    NODE* node = new NODE(w, v, level, parent, is, upb);
    prque.push(node);
    // 优先级队列不用标记产生的最优叶子节点 优先级队列到达叶子节点时即产生最优解
}
int Knapsack01_priority(vector<int>& weight, vector<int>& val, int cap) { // 优先级队列
    int n = weight.size();
    int i = 0;
    int cnt = 0;
    NODE* node = nullptr;
    int maxBound = maxbound(val, 0);
    while(i < n) {
        int wt = cw_ + weight[i];
        if(wt <= cap) {
            bestv = max(bestv, cv + val[i]);
            addLiveNODE(weight, wt, cv + val[i], i + 1, node, true, maxBound);
        }
        maxBound = maxbound(val, i + 1); // i + 1 表示第一个未被处理的下标
        if(maxBound >= bestv) { 
            addLiveNODE(weight, cw_, cv, i + 1, node, false, maxBound);
        }
        node = prque.top();
        prque.pop();
        maxBound = node->upbound;
        i = node->level;
        cw_ = node->weight;
        cv = node->value;
    }
    return bestv;
}
void test_Knapsack01_priority() {
    vector<int> weight = {16, 15, 15};
    vector<int> value = {45, 25, 25};
    int n = weight.size();
    int cap = 30;
    cout << "物品的重量:";
    for(int w : weight) cout << w << ' '; cout << endl;
    cout << "物品的价值:";
    for(int v : value) cout << v << ' '; cout << endl;
    cout << "背包的承重:" << cap << endl;
    cout << "装下的最大价值为:" << Knapsack01_priority(weight, value, cap) << endl;
    cw = 0; cv = 0; bestv = 0; cw_ = 0;
}

int main() {  
    test_containerLoading();
    cout << "-------------------------------------------------------------\n";
    test_Knapsack01_FIFO();
    cout << "-------------------------------------------------------------\n";
    test_Knapsack01_priority();
    cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";

    // cout << "-------------------------------------------------------------\n";
}

// 这TM啥
