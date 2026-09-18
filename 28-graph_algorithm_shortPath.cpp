#include <iostream>
#include <string> 
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <ranges>
#include <functional>

using namespace std;
using uint = unsigned int;
const uint INF = INT_MAX;
// 图实验代码———最短路径，迪杰斯特拉，弗洛伊德算法
// 邻接矩阵
class graph {
private:
    vector<vector<uint>> adjMatrix;           //邻接矩阵
    vector<vector<pair<int, uint>>> adjList;  //邻接表
public:
    graph(vector<vector<uint>>& matrix) {
        adjMatrix = matrix;
        adjList.resize(matrix.size());
        int n = matrix.size();
        for(int i = 0; i < n; i++) { // 根据邻接矩阵构造邻接表
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] != 0) adjList[i].emplace_back(j, matrix[i][j]);
            }
        }
    }
public:
    pair<uint, vector<int>> dijkstra_matrix(int start, int end) { // 迪杰斯特拉算法单源最短路径
        int n = adjMatrix.size();
        vector<uint> dis(adjMatrix.size(), INF);
        dis[start] = 0;
        vector<bool> use(adjMatrix.size(), false); // S集合
        vector<int> prev(n, -1);
        // 把start存到S集合
        use[start] = true;
        // 初始化start到其他U集合的距离
        for(int i = 0; i < adjMatrix.size(); i++) {
            dis[i] = adjMatrix[start][i];
            if(adjMatrix[start][i] != INF) prev[i] = start;
        }// 起点不显式入队，直接将起点的邻接顶点入队
        for(int i = 1; i < n; i++) { // 处理U集合
            // 先从U集合找到权值最小的顶点
            int k = -1;
            uint mn = INF;
            for(int j = 0; j < n; j++) {
                if(!use[j] && mn > dis[j]) {
                    mn = dis[j];
                    k = j;
                }
            }
            if(k == -1) return {}; // 无法到达
            use[k] = true; // 将U集合权值最小的顶点加入S集合
            // 更新U集合剩余顶点的权值
            for(int j = 0; j < n; j++) {
                if(!use[j] && dis[j] > adjMatrix[k][j] + mn) {
                    dis[j] = adjMatrix[k][j] + mn;
                    prev[j] = k;
                }
            }
        }
        vector<int> path;
        for(int at = end; at != -1; at = prev[at]) {
            path.push_back(at);
            if(at == start) break;
        }
        ranges::reverse(path);
        return {dis[end], path};
    }
    
    int dijkstra_matrix_prior(int start, int end) { // 利用优先队列对迪杰斯特拉算法优化
        int n = adjMatrix.size();
        vector<int> dis(n ,INF);
        vector<bool> use(n, false);
        dis[start] = 0;
        priority_queue<pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>> que; // pair的键是权值，值是下标
        for(int i = 0; i < n; i++) {
            dis[i] = adjMatrix[start][i];
            if(i != start && adjMatrix[start][i] != INF) que.emplace(adjMatrix[start][i], i);
        }
        while(!que.empty()) {
            auto p = que.top();
            que.pop();
            int k = p.second;
            int mn = p.first;
            if(use[k]) continue;
            use[k] = true;
            for(int j = 0; j < n; j++) {
                if(!use[j] && dis[j] > mn + adjMatrix[k][j]) {
                    dis[j] = mn + adjMatrix[k][j];
                    que.emplace(dis[j], j);
                }
            }
        }
        return dis.at(end);
    }
    int dijkstra_adjList(int start, int end) { // 迪杰斯特拉算法————邻接表写法
        int n = adjList.size();
        if(start == end) return 0;
        vector<bool> visited(n, false);
        vector<int> dis(n, INT_MAX);
        visited[start] = true;
        dis[start] = 0;
        for(auto& x : adjList[start]) {
            dis[x.first] = x.second;
        }
        for(int i = 1; i < n; i++) {
            int k = -1;
            int mn = INT_MAX;
            for(int j = 0; j < n; j++) {
                if(!visited[j] && mn > dis[j]) {
                    mn = dis[j];
                    k = j;
                }
            }
            if(k == -1) return -1;
            if(k == end) return dis[end];
            visited[k] = true;
            for(auto& x : adjList[k]) {
                if(!visited[x.first] && dis[x.first] > x.second + mn) {
                    dis[x.first] = x.second + mn;
                }
            }
        }
        return dis[end];
    }
    int dijkstra_adjList_prior(int start, int end) { // 迪杰斯特拉算法，邻接表写法，引入优先队列优化
        int n = adjList.size();
        vector<bool> visited(n, false);
        vector<uint> dis(n, INF);
        dis[start] = 0;
        visited[start] = true;
        priority_queue<pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>> que;
        for(auto& [x, y] : adjList[start]) {
            dis[x] = y;
            if(y != INF) {
                que.emplace(y, x);// 键是权值，值是下标
            }
        }
        while(!que.empty()) {
            auto p = que.top();
            que.pop();
            if(p.second == -1) return -1;
            if(visited[p.second]) continue;
            visited[p.second] = true;
            for(auto& [x, y] : adjList[p.second]) {
                if(!visited[x] && dis[x] > dis[p.second] + y) {
                    dis[x] = dis[p.second] + y;
                    que.emplace(dis[x], x);
                }
            }
        }
        return dis[end];
    }

    vector<vector<uint>> floyd_matrix() { // 多源最短路————Floyd算法
        int n = adjMatrix.size();
        vector<vector<uint>> dp(adjMatrix);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    dp[i][k] = min(dp[i][k], dp[i][j] + dp[j][k]);
                }
            }
        }
        return dp;
    }
};
int main() {
    vector<vector<uint>>matrix = 
    {
        {0, 6, 3, INF, INF, INF},
        {6, 0, 2, 5, INF, INF},
        {3, 2, 0, 3, 4, INF},
        {INF, 5, 3, 0, 2, 3},
        {INF, INF, 4, 2, 0, 5},
        {INF, INF, INF, 3, 5, 0},
    };
    graph gra(matrix);
    auto path = gra.dijkstra_matrix(0, 5);
    if(path.second.empty()) cout << "不存在路径" << endl;
    else {
        cout << "最短路径长度为" << path.first << endl;
        cout << "最短路径为:";
        for(int i = 0; i < path.second.size(); i++) {
            cout << path.second[i];
            if(i != path.second.size() - 1) cout << "->";
        }
        cout << endl;
    }
    cout << gra.dijkstra_matrix_prior(0, 5) << endl;
    cout << gra.dijkstra_adjList(0, 5) << endl;
    cout << gra.dijkstra_adjList_prior(0, 5) << endl;
    auto vec = gra.floyd_matrix();
    cout << "-------------------------------------------------------------\n";
    cout << "两点之间最小距离矩阵:" << endl;
    cout << "  0 1 2 3 4 5" << endl;
    int i = 0;
    for(auto v : vec) {
        cout << i++ << ' ';
        for(int x : v) {
            if(x == INF) cout << "F" << ' ';
            else cout << x << ' ';
        }
        cout << endl;
    }
}
