#include <iostream>
using namespace std;
//链式栈
struct Node{
    int data;
    Node *next;
    Node(int val=0){
        data=val;
        next=nullptr;
    }
};
class LinkStack{
    private:
    Node *head;
    Node *tail;
    int size_;
    public:
    LinkStack(){
        head = new Node();
        tail = head;
        size_=0;
    }
    ~LinkStack(){
        Node *p=head;
        while(p){
            p = head;
            head=head->next;
            delete p;
            p=head;
        }
    }
    void push(int val){//利用链表头插法实现入栈 
        Node *p=new Node(val);
        p->next = head->next;
        head->next=p;
        size_++;
        if(tail->next==nullptr){
            tail = p;
        }
    }
    void pop(){//出栈
        if(head->next==nullptr){
            throw "stack is empty";
        }
        Node *p=head->next;
        size_--;
        head->next=p->next;
        delete p;
    }
    int top() const{//获取栈顶元素
        if(head->next==nullptr){
            throw "stack is empty";
        }
        return head->next->data;
    }
    bool empty(){//判断栈是否为空
        return head->next == nullptr;
    }
    int size() const{
        return size_;
    }
};
int main(){
    LinkStack s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);
    cout<<s1.size()<<endl;
    while(!s1.empty()){
        cout<<s1.top()<<'\t';
        s1.pop();
    }
    cout<<endl;
    
    system("pause");
}