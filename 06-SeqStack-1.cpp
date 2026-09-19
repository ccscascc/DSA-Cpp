#include <iostream>
#include <cstring>
using namespace std;
//顺序表
class SeqStack{
    private:
    int *mpstack;
    int top;
    int cap;
    public:
    SeqStack(int size=10){
        cap=size;
        top=0;
        mpstack=new int[size];
    }
    ~SeqStack(){
        delete[]mpstack;
        mpstack=nullptr;
    }
    //栈操作方法
    void push(int val){//入栈
        if(top==cap){
            expand(2*cap);
        }
        mpstack[top++]=val;
    }
    void pop(){//出栈
        if(top==0){
            throw "栈为空\n";
        }
        top--;
    }
    int get_top(){//获取栈顶元素
        if(top==0)throw"empty\n";
        return mpstack[top -1];//栈为空时top==0,第一个元素入栈时top==1,第一个元素的下表为0，==top-1
    }
    int size(){//获取栈大小
        return cap;
    }
    bool empty(){//判断栈是否为空
        return top == 0;
    }
    private:
    void expand(int size){//栈扩容
        int *p=new int[size];
        memcpy(p,mpstack,top*sizeof(int));
        delete[]mpstack;
        mpstack=p;
        cap=size;
    }
};
int main(){
    SeqStack s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    while(!s1.empty()){
        cout<<s1.get_top()<<'\t';
        s1.pop();
    }
    cout<<endl;
    system("pause");
}
