#include <iostream>
using namespace std;
//环形队列--基于数组实现
class circle_queue{
    private:
    int *que;//指向堆内存
    int cap;//空间容量
    int front_;//队头
    int rear;//队尾
    int cnt;//队列元素个数
    public:
    circle_queue(int size=10){
        cap=size;
        front_=0;
        rear=0;
        cnt=0;
        que=new int[cap];
    }
    ~circle_queue(){
        delete[]que;
        que=nullptr;
    }
    void push(int val=0){//入队
        if((rear+1)%cap==front_){
            expand(2*cap);
        }
        que[rear]=val;
        rear=(rear+1)%cap;
        cnt++;
    }
    void pop(){//出队
        if(front_==rear){
            throw "队列为空";
        }
        front_=(front_+1)%cap;
        cnt--;
    }
    int front()const{//获取队头元素
        if(front_==rear)throw;
        return que[front_];
    }
    int back()const{//获取队尾元素
        if(front_==rear)throw;
        return que[(rear-1+cap)%cap];//若队尾元素恰好是数组的最后一个，及rear是0，则返回end,否则返回rear-1处元素
    }
    bool empty(){
        return front_==rear;
    }
    int size(){//队列元素个数 O(1)
        //通过添加成员变量cnt
        return cnt;
    }
    int count(){//统记队列元素个数 O(n)
        //没有成员变量cnt,遍历数组实现统计个数
        int cnt_=0;
        for(int i=front_;i!=rear;i=(i+1)%cap){
            cnt_++;
        }
        return cnt_;
    }
    void clear(){//清空队列
        while(!empty()){
            pop();
        }
    }
    private:
    void expand(int size){//扩容
        int *p=new int[size];
        int i,j=front_;
        for(i=0;j!=rear;i++,j=(j+1)%cap){
            p[i]=que[i];
        }
        delete[]que;
        que=p;
        delete[] p;
        cout<<cap<<endl;
        p=nullptr;
        rear=i;
        cap=size;
        front_=0;
    }
};
int main(){
    circle_queue cq1;
    cq1.push(10);
    cout<<cq1.front()<<endl;
    cq1.pop();
    cout<<cq1.size()<<endl;
    cq1.push(1);
    cq1.push(2);
    cq1.clear();
    cout<<cq1.size();
    system("pause");
}