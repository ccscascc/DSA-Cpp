#include <iostream>

using namespace std;

enum State{//状态枚举
    STATE_USING,//正在被使用
    STATE_UNUSE,//从未被使用
    STATE_DELETE//曾被使用，元素被删除
};
struct Bucket{
    
    int key;//桶存储的数据
    State state;//桶的状态
    Bucket(int k = 0, State s = STATE_UNUSE){
        key = k;
        state = s;
    }
};
class Linear_probing_Hash_Table_{
    private:
    Bucket *table;//指向动态开辟的哈希表
    int table_size;//哈希表总长度
    int use_bucket_number;//使用桶的个数
    double Load_Factor;//装载因子
    static const int Prime_size = 10;//素数表大小
    static int Primes[Prime_size];//素数表
    int Prime_idx;//当前使用的素数下标
    public:
    Linear_probing_Hash_Table_(int size_ = Primes[0], double x = 0.75){
        int i;
        for(i = 0; i < Prime_size; i++){
            if(Primes[i] >= size_){
                size_ = Primes[i];
                break;
            }
        }
        if(size_ > Primes[Prime_size - 1]){
            size_ = Primes[Prime_size - 1];
            i = Prime_size - 1;
        }
        Prime_idx = i;
        table_size = size_;
        Load_Factor = x;
        use_bucket_number = 0;
        table = new Bucket[table_size];
    }
    ~Linear_probing_Hash_Table_(){
        delete[]table;
        table = nullptr;
    }
    public:
    bool insert(int key){//插入元素
        double factor = (double)use_bucket_number / (double)table_size;//考虑是否扩容
        //cout << "插入前装载因子:" << factor << endl;
        //cout << table_size << '\t' << use_bucket_number << endl;
        if(factor > Load_Factor){
            expand();//当前个数/容量大于装载因子,哈希表扩容
        }
        int idx = key % table_size;
        
        int i = idx;
        do{
            if(table[i].state != STATE_USING){
                table[i].state = STATE_USING;
                table[i].key = key;
                use_bucket_number++;
                //factor = (double)use_bucket_number / (double)table_size;
                //cout << "插入后装载因子:" << factor << endl;
                return true;
            }
            i = (i + 1) % table_size;
        }while(i != idx);
        
        return false;
    }
    void erase(int key){//按key元素删除
        int idx = key % table_size;
        int i = idx;
        do{
            if(table[i].key == key && table[i].state == STATE_USING){
                table[i].state = STATE_DELETE;
                use_bucket_number--;
            }
            i = (i + 1) % table_size;
        }while(i != idx && table[i].state != STATE_UNUSE);
    }
    bool find(int key){//按key查询元素
        int idx = key % table_size;
        int i = idx;
        do{
            if(table[i].key == key && table[i].state == STATE_USING){
                return true;
            }
            i = (i + 1) % table_size;
        }while(i != idx && table[i].state != STATE_UNUSE);
        return false;
    }
    int count(int key){//统计键值为key的个数
        int idx = key % table_size;
        int i = idx;
        int cnt = 0;
        do{
            if(table[i].key == key && table[i].state == STATE_USING){
                cnt++;
            }
            i = (i + 1) % table_size;
        }while(i != idx && table[i].state != STATE_UNUSE);
        return cnt;
    }
    private:
    void expand(){//扩容
        Prime_idx++;
        if(Prime_idx == Primes[Prime_size-1])throw"数据量过大";
        Bucket *newtable = new Bucket[Primes[Prime_idx]];
        for(int i = 0; i < table_size; i++){
            if(table[i].state == STATE_USING){//旧表中有效的数据重新哈希放入新扩容的哈希表中
                int idx = table[i].key % Primes[Prime_idx];
                int k = idx;
                do{
                    if(newtable[k].state != STATE_USING){
                        newtable[k].state = STATE_USING;
                        newtable[k].key = table[i].key;
                        k = (k + 1) % Primes[Prime_idx];
                        break;
                    }
                }while(k != idx);
            }
        }
        delete[]table;
        table = newtable;
        table_size = Primes[Prime_idx];
    }
};
int Linear_probing_Hash_Table_::Primes[Prime_size] = {3, 7, 23, 47, 97, 251, 443, 991, 1471, 2767};
int main(){
    Linear_probing_Hash_Table_ hash1;
    hash1.insert(21);
    hash1.insert(12);
    hash1.insert(15);
    hash1.insert(32);
    hash1.insert(1);
    cout << hash1.find(1) << endl;
    hash1.insert(1);
    cout << hash1.count(1) << endl;
    hash1.erase(21);
    cout << hash1.find(21) << endl;
    system("pause");
    return 0;
}
 //哈哈哈哈哈哈哈
 //希希希希希希希