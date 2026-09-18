#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <cstdint>
#include <queue>

using namespace std;
// 图实验代码————邻接表 构建邻接表（文件读写）(无权图)
class Digraph {
private:
    struct Vertic {
        string data; // 顶点信息
        list<int> adjList; // 邻接链表
        Vertic(string d = "") {
            data = d;
        }
    };
    vector<Vertic> vertics; // 图的结构邻接表
public:
size_t size() {
    return vertics.size() - 1;
}
    void readFile(string filePath) { // 构造邻接表
        FILE *pf = fopen(filePath.c_str(), "r");
        if(pf == nullptr) {
            perror("fopen error");  // 会显示具体错误
            throw;
        }
        vertics.emplace_back(""); // 占用vertics[0]
        while(!feof(pf)) {
            char line[128] = {0};
            fgets(line, 128, pf); // 读取一行字符存入line中
            string linestr(line); // 去掉\ \n
            linestr.erase(remove_if(linestr.begin(), linestr.end(), [](char c){return c == '\n' || c == '\r';}), linestr.end());
            if(linestr.empty()) break;
            vertics.emplace_back(linestr);// 增加一个节点信息 此处是将顶点的名字存入邻接表中
            fgets(line, 128, pf);
            char* vers = strtok(line, ","); // strtok() ,将字符串以参数2为分隔符拆分成多个token
            while(vers != nullptr) {
                string s = string(vers);
                // s.erase(remove_if(s.begin(), s.end(), [](char c){return c == '\n' || c == '\r';}), s.end());
                if(s.back() == '\n') s.pop_back(); // 这里对邻接表的字符处理
                if(atoi(vers) > 0) vertics.back().adjList.emplace_back(stoi(s)); // atoi() 字符串转整数 
                // *** 此处的vers是char*类型，若需让char接受需解引用
                vers = strtok(nullptr, ","); // strtok()是一个有状态的函数，此处的nullptr类似书签，表示从上次结束的地方继续读取
            }
        }
        fclose(pf);
    }
    void show() const { // 输出邻接表信息
        int a = 0;
        for(auto ver : vertics) {
            if(a++ == 0) continue;
            cout << ver.data << ":";
            if(ver.adjList.empty() || ver.adjList.front() == 0) {
                cout << "无邻接顶点" << endl;
                continue;
            }
            for(auto no : ver.adjList) {
                cout << vertics[no].data << " ";
            }
            cout << endl;
        }
    }
    int findVertic(string str) {
        for(int i = 1; i < (int)vertics.size(); i++) {
            if(vertics[i].data == str) return i;
        }
        return -1;
    }
    void addVertics(string ver) {
        if(findVertic(ver) != -1) {
            cout << "顶点" << ver << "已存在" << endl;
            return;
        }
        vertics.emplace_back(ver);
        vertics.back().adjList.emplace_back(0);
        cout << "顶点插入成功" << endl;
    }
    void addEdges(string ver, vector<string>& edges) {
        int pos = findVertic(ver);
        unordered_set<string> s; // 哈希表去重
        if(pos == -1) {
            cout << "不存在名为" << ver << "的顶点" << endl;
            return;
        }
        else if(vertics[pos].adjList.empty() || vertics[pos].adjList.front() != 0) {
            for(auto ver : vertics[pos].adjList) {
                s.insert(vertics[ver].data);
            }
            for(auto& edge : edges) {
                if(s.find(edge) == s.end()) vertics[pos].adjList.emplace_back(findVertic(edge));
            }
        }
        else {
            vertics[pos].adjList.clear();
            for(auto& edge : edges) {
                vertics[pos].adjList.emplace_back(findVertic(edge));
            }
        }
    }
    void test() {
        for(auto ver : vertics) {
            cout << ver.data << ' ';
            for(auto adj : ver.adjList) {
                cout << adj << ' ';
            }
            cout << endl;
        }
    }
    void saveVertics() {
        FILE* file = fopen("C:/Users/lzy58/Desktop/shujujiegou/data.txt", "w");
        for(int i = 1; i < (int)vertics.size(); i++) {
            fprintf(file, "%s\n", (vertics[i].data.c_str()));
            bool first = true;
            for(auto adj : vertics[i].adjList) {
                if(!first) fprintf(file, ",");
                first = false;
                fprintf(file, to_string(adj).c_str());
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
private:
    void dfs(int start, vector<bool>& visited) { // 图的深度优先遍历 递归接口
        if(visited[start]) return; // 该start已被遍历过
        cout << vertics[start].data << ' ';
        visited[start] = true;
        // 递归遍历下一个邻接顶点
        for(auto& no : vertics[start].adjList) {
            dfs(no, visited);
        }
    }
public:
    void dfs() { // 广度优先遍历
        vector<bool> visited(vertics.size());
        return dfs(1, visited);
    }
    void bfs(int start = 1) {
        queue<Vertic> que;
        vector<bool> visited(vertics.size(), false);
        que.push(vertics[start]);
        visited[start] = true;
        while(!que.empty()) {
            auto front = que.front();
            que.pop();
            cout << front.data << ' ';
            for(auto& no : front.adjList) {
                if(!visited[no]) que.push(vertics[no]);
                visited[no] = true;
            }
        }
    }
    vector<int> shortPath(int start, int end) { // 利用广度优先遍历求解无权图的最短路径问题
        int n = vertics.size();
        queue<int> que;
        vector<bool> visited(n, false);
        vector<int> mark(n, 0); // 记录每个顶点是从哪里来的
        que.push(start);
        if(start == end) {
            if(ranges::find(vertics[start].adjList, start) == vertics[start].adjList.end()) {
                for(int ad : vertics[start].adjList) {
                    if(!visited[ad]) {
                        que.push(ad);
                        visited[ad] = true;
                        mark[ad] = start;
                    }
                }
                while(!que.empty()) {
                    int front = que.front();
                    que.pop();
                    for(int no : vertics[front].adjList) {
                        if(!visited[no]) {
                            que.push(no);
                            visited[no] = true;
                            mark[no] = front;
                        }
                        if(no == start) {
                            vector<int> path;
                            while(end != 0) {
                                path.push_back(end);
                                end = mark[end];
                                mark[start] = 0;
                            }
                            ranges::reverse(path);
                            return path;
                        }
                    }
                }
                
                if(que.empty()) return{};
            }
            else return {start, end};
        }
        visited[start] = true;
        while(!que.empty()) {
            int front = que.front();
            if(front == end) { // 找到end
                break;
            }
            que.pop();
            for(auto& no : vertics[front].adjList) {
                if(!visited[no]){
                    visited[no] = true;
                    que.push(no);
                    mark[no] = front;
                }
            }
        }
        if(que.empty()) return {};
        else {
            vector<int> path;
            while(end != 0) {
                path.push_back(end);
                end = mark[end];
            }
            ranges::reverse(path);
            return path;
        }
    }
    string getData(int idx) {
        return vertics[idx].data;
    }
    int dijkstra(int start, int end) { // 迪杰斯特拉算法————邻接表写法，无权图的边权视为全都是1
        int n = vertics.size();
        vector<bool> visited(n, false);
        vector<int> dis(n, INT_MAX);
        visited[start] = true;
        dis[start] = 0;
        for(auto& x : vertics[start].adjList) {
            dis[x] = 1;
        }
        for(int i = 2; i < n; i++) {
            int k = -1;
            int mn = INT32_MAX;
            for(int j = 1; j < n; j++) {
                if(!visited[j] && mn > dis[j]) {
                    mn = dis[j];
                    k = j;
                }
            }
            if(k == -1) return -1;
            if(k == end) return dis[end];
            visited[k] = true;
            for(auto& x : vertics[k].adjList) {
                if(!visited[x] && dis[x] > 1 + mn) {
                    dis[x] = i + mn;
                }
            }
        }
        return dis[end];
    }
};
int main() {
    Digraph dg;
    dg.readFile("C:/users/lzy58/Desktop/shujujiegou/data.txt");
    dg.show();
    cout << "-------------------------------------------------------------\n";
    string str = "A";
    cout << "存储" << str << "的顶点";
    int flag = dg.findVertic(str);
    if(flag == -1) cout << "不存在" << endl;
    else cout << "存在,在邻接表中下标为" << flag << endl;
    cout << "-------------------------------------------------------------\n";
    dg.addVertics("Z");
    vector<string> edges = {"A", "C", "D"};
    dg.addEdges("Z", edges);
    dg.saveVertics();
    cout << "-------------------------------------------------------------\n";
    // cout << __cplusplus << endl;
    cout << "深度优先遍历:";
    dg.dfs();
    cout << endl;
    cout << "广度优先遍历:";
    dg.bfs();
    cout << endl;
    cout << "-------------------------------------------------------------\n";
    int start = 1, end = 1;
    vector<int> path = dg.shortPath(start, end);
    if(!path.empty()) {
        for(int i = 0; i < path.size(); i++) {
            cout << dg.getData(path[i]);
            if(i < path.size() - 1) cout << "->";
        }
        cout << endl;
    }
    else cout << "不存在从" << dg.getData(start) << "到" << dg.getData(end)<< "的路径" << endl;
    cout << "-------------------------------------------------------------\n";
}