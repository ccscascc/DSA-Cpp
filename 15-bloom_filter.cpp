#include <iostream>
#include <string>
#include <vector>
#include <variant>
using namespace std;
// 简易布隆过滤器
class bloom_filter{
    private:
    vector<bool>bitmap;
    int bit_size;
    public:
    bloom_filter(int size = 371){
        bit_size = size;
        bitmap.resize(bit_size);
    }
    private:
    int Hash1(const string &str){
        int res = 0;
        for(char c : str){
            res = (res * 137 + c) % bit_size;
        }
        return res;
    }
    int Hash2(const string &str){
        int res = 0;
        for(char c : str){
            res = (res * 17 + c) % bit_size;
        }
        return res;
    }
    int Hash3(const string &str){
        int res = 0;
        for(char c : str){
            res = (res * 37 + c) % bit_size;
        }
        return res;
    }
    public:
    void insert(const string& key){//插入
        bitmap[Hash1(key)] = true;
        bitmap[Hash2(key)] = true;
        bitmap[Hash3(key)] = true;
    }
    bool find(const string &key){//查找
        bool x = true;
        if(!bitmap[Hash1(key)]){
            x = false;
        }
        if(!bitmap[Hash2(key)]){
            x = false;
        }
        if(!bitmap[Hash3(key)]){
            x = false;
        }
        return x;
    }
};
int main(){
    bloom_filter bf1;
    cout << bf1.find("sss") << endl;
    bf1.insert("aaa");
    cout << bf1.find("a") << endl;
    cout << bf1.find("aaa") << endl;
    system("pause");
}
