#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <ranges>
#include <algorithm>
using namespace std;

// 图实验代码————十字链表

class digraph {
    struct edge;
    struct vertex {
        string data;
        edge* inHead;
        edge* inTail;
        edge* outHead;
        edge* outTail;
        vertex(string d) {
            data = d;
            inHead = nullptr;
            inTail = nullptr;
            outHead = nullptr;
            outTail = nullptr;
        }
        bool operator==(const vertex& ver)const {
            return ver.data == data;
        }
    };
    struct edge {
        string inVer;
        string outVer;
        edge* inNext;
        edge* outNext;
        edge(string in, string out) {
            inVer = in;
            outVer = out;
            inNext = nullptr;
            outNext = nullptr;
        }
        bool operator==(const edge& e)const {
            return e.inVer == inVer && e.outVer == outVer;
        }
    };
    vector<vertex> vertexs; // 顶点
public:
    digraph() {}
    void addVertex(string d) {
        vertexs.emplace_back(d);
    }
    int findVertex(string d) {
        vertex tmp(d);
        auto it = find(vertexs.begin(), vertexs.end(), tmp);
        return it == vertexs.end() ? -1 : it - vertexs.begin();
    }
    void addEdge(string in, string out) {
        int iv = findVertex(in), ov = findVertex(out);
        if(iv == -1 || ov == -1) return;
        edge* e = new edge(in, out);
        if(vertexs[iv].inHead == nullptr) {
            vertexs[iv].inHead = e;
            vertexs[iv].inTail = vertexs[iv].inHead;
        }
        else {
            vertexs[iv].inTail->inNext = e;
            vertexs[iv].inTail = vertexs[iv].inTail->inNext;
        }
        if(vertexs[ov].outHead == nullptr) {
            vertexs[ov].outHead = e;
            vertexs[ov].outTail = vertexs[ov].outHead;
        }
        else {
            vertexs[ov].outTail->outNext = e;
            vertexs[ov].outTail = vertexs[ov].outTail->outNext;
        }
    }
    ~digraph() {
        vector<edge*> edges;
        int n = vertexs.size();
        for(auto& ver : vertexs) {
            edge* cur = ver.inHead;
            while(cur) {
                if(find(edges.begin(), edges.end(), cur) == edges.end()) edges.push_back(cur);
                cur = cur->inNext;
            }
        }
        for(auto& e : edges) delete e;
    }
    void print() {
        for(auto& vers : vertexs) {
            cout << vers.data << "\n" << "入边表:";
            auto ptr = vers.inHead;
            if(ptr == nullptr) cout << "入边表为空";
            while(ptr) {
                cout << '(' << ptr->inVer << "," << ptr->outVer << ")";
                if(ptr->inNext) cout << ',';
                ptr = ptr->inNext;
            }
            cout << endl;

            cout << "出边表:";
            ptr = vers.outHead;
            if(ptr == nullptr) cout << "出边表为空";
            while(ptr) {
                cout << '(' << ptr->inVer << "," << ptr->outVer << ")";
                if(ptr->outNext) cout << ',';
                ptr = ptr->outNext;
            }
            cout << endl;
        }
    }
};
int main() {
    digraph d;
    for(char i = 'a'; i < 'e'; i++) {
        string str = "A"; str += i; 
        d.addVertex(str);
    }
    d.addEdge("Aa", "Ac"); d.addEdge("Aa", "Ad"); d.addEdge("Ad", "Aa");
    d.print();
    return 0;
}