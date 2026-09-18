#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <queue>

using namespace std;
// 并查集实验代码
class DSU {
private:
    vector<int> parent;
    int cnt;
    vector<int> rank;
public:
    DSU(int s) {
        cnt = s;
        parent.resize(s);
        for(int i = 0; i < cnt; i++) {
            parent[i] = i; // 记录父节点，初始父节点为自己，即每一个结点都是独立的树
        }
        rank.resize(s, 1);
    }
    int DSU_find(int x) { // 
        int y = x;
        while(x != parent[x]) {
            x = parent[x];
        }
        while(y != parent[y]) { // 路径压缩：找到后将找到的结点以及路径上的结点的父节点置为root
            int tmp = y;
            y = parent[y];
            parent[tmp] = x;
        }
        return x;
    }
    int DSU_rfind(int x) { // 并查集查找，递归
        if(x == parent[x]) return x;
        return parent[x] = DSU_rfind(parent[x]);
    }
    void merge(int x, int y) { // 并查集——并
        x = DSU_find(x), y = DSU_find(y);
        if(x == y) return;
        // parent[y] = x; // 把y所在集合的根节点挂到x所在集合的根节点下
        // ↑问题：永远是一个方向上的父子关系, 极端情况下可能退化为链表，效率低
        
        // 采用加权标记，将rank值（即层高）小的挂在rank值大的下面
        if(rank[x] > rank[y]) parent[y] = x;
        else {
            parent[x] = y;
            rank[y] = max(rank[y], rank[x] + 1);
        }
    }
    pair<int, vector<vector<int>>> Kruskal(int n, vector<vector<int>>& edges) { // 最小生成树——Kruskal算法
        int m = edges.size();
        sort(edges.begin(), edges.end(), [](vector<int>& e1, vector<int>& e2){return e1[2] < e2[2];});
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
        vector<vector<int>> p;
        int load = 0;
        for(int i = 0; i < m; i++) { // 按小到大选边，即合并这条边的两个顶点，前提是两个顶点不在一个集合中
            int x = DSU_find(edges[i][0]), y = DSU_find(edges[i][1]);
            if(x == y) continue;
            merge(x, y);
            p.push_back(edges[i]);
            load += edges[i][2]; // 记录最小生成树的边
        }
        return make_pair(load, p);
    }
    pair<int, vector<vector<int>>> prim_priority(int n, vector<vector<int>>& edges) { // 最小生成树prim算法，邻接表+优先队列优化 
        int m = edges.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
        vector<bool> intree(n, false);
        vector<int> key(n, INT_MAX);
        vector<vector<pair<int, int>>> adjList(n);
        for(int i = 0; i < m; i++) {
            adjList[edges[i][0]].emplace_back(edges[i][2], edges[i][1]);
            adjList[edges[i][1]].emplace_back(edges[i][2], edges[i][0]);
        }
        for(int i = 0; i < n; i++) parent[i] = i;
        key[0] = 0;
        que.emplace(0, 0);
        int totalW = 0;
        vector<vector<int>> load;
        while(!que.empty()) {
            auto [w, u] = que.top();
            que.pop();
            if(intree[u]) continue;
            if(parent[u] != u) load.push_back({parent[u], u, w});   
            intree[u] = true;
            totalW += w;
            for(auto& e : adjList[u]) {
                if(!intree[e.second] && key[e.second] > e.first) {
                    key[e.second] = e.first;
                    que.emplace(e.first, e.second);
                    parent[e.second] = u;
                }
            }
        }
        return make_pair(totalW, load);
    }
    pair<int, vector<vector<int>>> prim_matrix(int n, vector<vector<int>> edges) { // 最小生成树prim算法，邻接矩阵
        vector<vector<int>> matrix(n, vector<int>(n, 1e9));
        for(auto& e : edges) { // 邻接矩阵
            matrix[e[0]][e[1]] = e[2];
            matrix[e[1]][e[0]] = e[2];
        }
        for(int i = 0; i < n; i++) parent[i] = i;
        vector<int> key(n, 1e9); // 存储该节点到已加入集合的最小边权
        vector<int> intree(n, false);
        intree[0] = true; // 初始最小生成树的顶点
        vector<vector<int>> load;
        key[0] = 0;
        int totalW = 0;
        for(int i = 0; i < n; i++) { // 对第一个顶点处理
            matrix[i][i] = 0;
            key[i] = matrix[0][i];
            if(matrix[0][i] < 1e9) { 
                parent[i] = 0;
            }
        }
        for(int i = 0; i < n; i++) {
            int mn = 1e9;
            int k = -1;
            for(int j = 0; j < n; j++) {
                if(!intree[j] && key[j] < mn) { // 选一个代价最小的边对应的顶点
                    mn = key[j];
                    k = j;
                }
            }
            if(k == -1) continue;
            intree[k] = true;
            if(k != parent[k]) {
                load.push_back({parent[k], k, matrix[parent[k]][k]});
                totalW += mn;
            }
            for(int j = 0; j < n; j++) {
                if(!intree[j] && key[j] > matrix[k][j]) {
                    key[j] = matrix[k][j];  
                    parent[j] = k;
                }
            }
        }
        return make_pair(totalW, load);
    }
};

int main() {
    DSU dsu(9);
    dsu.merge(7, 8);
    dsu.merge(6, 8);
    cout << dsu.DSU_find(8) << endl;
    cout << dsu.DSU_find(6) << endl;
    vector<vector<int>> edges = {
        {0, 1, 4},
        {0, 2, 1},  
        {1, 2, 2}, 
        {1, 3, 5},  
        {2, 3, 3}   
    };
    DSU d(5);
    auto x = d.Kruskal(5, edges);
    cout << "最小生成树总花费:" << x.first << endl;
    cout << "最小生成树:" << endl;
    for(int i = 0; i < (int)x.second.size(); i++) {
        cout << x.second[i][0] << " -> " << x.second[i][1] << " cost = " << x.second[i][2] << endl;
    }
    cout << "-------------------------------------------------------------\n";
    x = d.prim_priority(5, edges);
    cout << "最小生成树总花费:" << x.first << endl;
    cout << "最小生成树:" << endl;
    for(int i = 0; i < (int)x.second.size(); i++) {
        cout << x.second[i][0] << " -> " << x.second[i][1] << " cost = " << x.second[i][2] << endl;
    }
    cout << "-------------------------------------------------------------\n";
    x = d.prim_matrix(5, edges);
    cout << "最小生成树总花费:" << x.first << endl;
    cout << "最小生成树:" << endl;
    for(int i = 0; i < (int)x.second.size(); i++) {
        cout << x.second[i][0] << " -> " << x.second[i][1] << " cost = " << x.second[i][2] << endl;
    }
    cout << "-------------------------------------------------------------\n";
}