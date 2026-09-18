#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;
// trie字典树实验代码
class Trie{
    private:
    struct TrieNode { // 字典树结点
        int freqs; // 单词末尾字符存储单词的数量（频率）
        char ch; // 当前结点存储的字符
        map<char, TrieNode*> nodemp; //存储孩子结点字符数据和结点指针的对应关系
        TrieNode(char c, int f) {
            freqs = f;
            ch = c;
        }
    };
    TrieNode* root = nullptr; //根节点 
    size_t cnt;
    public:
    Trie() { // 构造函数 根节点
        root = new TrieNode('\0', 0); // root内不存放任何字符
        cnt = 0;
    }
    ~Trie() { // 析构函数
        TrieNode* cur = root;
        queue<TrieNode*> que;
        que.push(root);
        while(!que.empty()) {
            TrieNode* front = que.front();
            que.pop();
            for(auto& pair : front->nodemp) {
                que.push(pair.second); // 取出当前结点
            }
            delete front; // 释放当前结点
        }
    }
    private:
    void preorder(TrieNode* cur, vector<string>& words, string word) { // 前序遍历实现有序存放到列表中
        if(cur != root) {
            word.push_back(cur->ch);
            if(cur->freqs > 0) {
                words.push_back(word);
            }
        }
        for(auto& pair : cur->nodemp) {
            preorder(pair.second, words, word);
        }
    }
    public:
    int size() {
        return cnt;
    }
    void addWord(const string& wd) { // 在trie树上添加单词 
        TrieNode* cur = root;
        int n = wd.size();
        for(int i = 0; i < n; i++) {
            map<char, TrieNode*>::iterator childIt = cur->nodemp.find(wd[i]);
            if(childIt != cur->nodemp.end()) { // 当前结点的孩子结点有存储wd[i]的结点，则从这个结点继续搜索
                cur = childIt->second;
            }
            else { // 当前结点没有存储wd[i] 的结点，则新建并从此节点继续搜索
                TrieNode* child = new TrieNode(wd[i], 0);
                // cur->nodemp.insert(make_pair(wd[i], child)); // 构造临时pair，有开销
                cur->nodemp.emplace(wd[i], child); // 原地构造更高效
                cur = child; // 从child继续查找
            }
        }
        // 此时cur指向插入单词在字典树上的叶子节点
        cur->freqs++;
        if(cur->freqs == 1) cnt++;
    }
    int queryWord(const string& wd) { // 查询单词 返回单词出现次数
        if(wd.empty()) return 0;
        TrieNode* cur = root;
        int n = wd.size();
        for(int i = 0; i < n; i++) {
            auto childIt = cur->nodemp.find(wd[i]);
            if(childIt != cur->nodemp.end()) {
                cur = childIt->second;
            }
            else return 0;
        }
        return cur->freqs;
    }
    void outPutWords() { // 前序遍历字典树实现按顺序输出
        TrieNode* node = root;
        vector<string> words;
        preorder(node, words, "");
        int cnt = 0;
        for(string& wd : words) {
            cout << wd << '\t';
            if(++cnt % 5 == 0) {
                cout << endl;
            }
        }
        cout << endl;
    }
    vector<string> queryPrefix(const string& prefix) { // 前缀搜索
        TrieNode* cur = root;
        int n = prefix.size();
        for(int i = 0; i < n; i++) {
            auto childIt = cur->nodemp.find(prefix[i]);
            if(childIt == cur->nodemp.end()) {
                return {};
            }
            else {
                cur = childIt->second;
            }
        }
        // 此时cur指向prefix最后一个字符
        vector<string> words;
        preorder(cur, words, prefix.substr(0, n - 1));
        return words;
    }
    void removeWord(const string& word) { // 删除单词
        TrieNode* cur = root;
        TrieNode* del = root;
        int n = word.size();
        char delch = word[0];
        for(int i = 0; i < n; i++) {
            auto childIt = cur->nodemp.find(word[i]);
            if(childIt == cur->nodemp.end()) {
                return;
            }
            cur = childIt->second;
            if(cur->freqs > 0 || cur->nodemp.size() > 1) { // 这个字母在另一个单词的同样位置出现
                del = cur; // del 指向word 最后一个freqs不为0的字符节点
                delch = word[i];
            }
        }
        // word存在，此时cur指向单词在trie里面的末尾结点
        if(cur->nodemp.empty()) {
            TrieNode* child = del->nodemp[delch];
            del->nodemp.erase(delch);
            queue<TrieNode*> que;
            que.push(child);
            while(!que.empty()) {
                TrieNode* front = que.front();
                que.pop();
                for(auto& pair : front->nodemp) {
                    que.push(pair.second);
                }
                delete front;
            }
        }
        else {
            cur->freqs = 0; // 当前单词末尾字符结点后面还有别的字符，不能删除，只将freqs置为0
        }
    }
};
int main() {
    Trie trie;
    cout << "0.退出" << endl;
    cout << "1.添加单词" << endl;
    cout << "2.查询单词" << endl;
    cout << "3.查看所有单词" << endl;
    cout << "4.按前缀搜索单词" << endl;
    cout << "5.删除单词" << endl;
    cout << "6.查看当前单词数量" << endl;
    int cmd;
    while(true) {
        cout << "输入选项:";
        cin >> cmd;
        if(cmd == 0) break;
        else if(cmd == 1) {
            string s;
            cout << "输入要添加的单词:";
            cin >> s;
            trie.addWord(s);
        }
        else if(cmd == 2) {
            string s;
            cout << "输入要查询的单词:";
            cin >> s;
            cout << "单词出现次数为" << trie.queryWord(s) << endl;
        }
        else if(cmd == 3) {
            trie.outPutWords();
        }
        else if(cmd == 4) {
            string prefix;
            cout << "输入要查找的前缀:";
            cin >> prefix;
            vector<string> words = trie.queryPrefix(prefix);
            cout << "查询结果:" << endl;
            int cnt = 0;
            for(string& wd : words) {
                cout << wd << '\t';
                if(++cnt % 5 == 0) cout << endl;
            }
            cout << endl;
        }
        else if(cmd == 5) {
            string word;
            cout << "输入要删除的单词:" << endl;
            cin >> word;
            trie.removeWord(word);
        }
        else if(cmd == 6) {
            cout << "当前有" << trie.size() << "个单词" << endl;
        }
        else continue;
    }
}