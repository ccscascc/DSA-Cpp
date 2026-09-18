#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
//链式哈希表
//模拟 unordered_set
class Link_Hash_Table_{
    private:
    vector<list<int>>table;//哈希表的数据结构
    int Use_Bucket_Num;//已使用的桶的个数
    int table_size;//桶的个数
    double Load_factor;//装载因子
    static const int Prime_size = 10;//素数表大小
    static int Primes[Prime_size];//素数表
    int Prime_idx;//当前使用的素数下标
    public:
    Link_Hash_Table_(int size_ = Primes[0], double loadfactor = 0.75){
        Use_Bucket_Num = 0;
        Load_factor = loadfactor;
        for(int i = 0; i < Prime_size; i++){
            if(Primes[i] >= size_){
                size_ = Primes[i];
                Prime_idx = i;
                break;
            }
        }
        if(Primes[Prime_size-1] < size_){
            throw "too long";
        }
        table.resize(Primes[Prime_idx]);
        table_size = table.size();
    }
    ~Link_Hash_Table_(){}//无堆内存
    public:
    bool insert(int key){//插入
        double factor = (double)Use_Bucket_Num / (double)table.size();
        //cout << "插入前装载因子:" << factor << endl;
        if(factor > Load_factor){
            expand();//达到装载因子最大值，进行扩容
        }
        int idx = key % table.size();
        if(table[idx].empty()){
            Use_Bucket_Num++;
            table[idx].emplace_back(key);
            //double factor = (double)Use_Bucket_Num / (double)table.size();
        //cout << "插入后装载因子:" << factor << endl;
            return true;
        }
        else{
            //使用全局的泛型算法，而不是调用自己的成员方法，避免重名产生误解
            auto it = ::find(table[idx].begin(),table[idx].end(),key);
            if(it == table[idx].end()){
                table[idx].emplace_back(key);
                //double factor = (double)Use_Bucket_Num / (double)table.size();
        //cout << "插入后装载因子:" << factor << endl;
                return true;
            }
            else return false;
        }
        return false;
    }
    bool erase(int key){//删除
        int idx =  key % table.size();
        if(table[idx].empty())return false;
        else{
            auto it = ::find(table[idx].begin(),table[idx].end(),key);
            if(it != table[idx].end()){
                table[idx].erase(it);
                if(table[idx].empty()){
                    Use_Bucket_Num--;
                }
                return true;
            }
            else return false;
        }
    }
    bool find(int key){//查找
        int idx = key % table.size();
        auto it = ::find(table[idx].begin(),table[idx].end(),key);
        return it != table[idx].end();
    }
    private:
    void expand(){//哈希表扩容
        if(Prime_idx == Prime_size - 1)throw"too long";
        Prime_idx++;
        vector<list<int>>old_table;
        table.swap(old_table);
        table.resize(Primes[Prime_idx]);
        table_size = table.size();
        //链式哈希表中扩容后可能占用桶个数可能会改变
        //即use_bucket_number可能改变，需要重新计数
        Use_Bucket_Num = 0;
        for(auto list : old_table){
            
            for(auto key : list){
                int idx = key % table.size();

                if(table[idx].empty()){
                    Use_Bucket_Num++;
                }
                table[idx].emplace_back(key);
            }
        }
    }
};
int Link_Hash_Table_::Primes[Prime_size] = {3, 7, 23, 47, 97, 251, 443, 991, 1471, 2767};//素数表
int main(){
    Link_Hash_Table_ hash1;
    hash1.insert(10);
    hash1.insert(20);
    hash1.insert(22);
    hash1.insert(3);
    hash1.insert(1);
    cout << hash1.find(1) << endl;
    hash1.erase(1);
    cout << hash1.find(1) << endl;
    system("pause");
}
 //哈哈哈哈哈哈哈
 //希希希希希希希