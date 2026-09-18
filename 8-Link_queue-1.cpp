#include <iostream>
using namespace std;
// 链式队列
//基于双向循环链表实现环形队列
struct Node{
    int data;//数据域
    Node *next;//指向下一个结点
    Node *pre;//指向上一个结点
    Node(int val=0){
        data = val;
        next = nullptr;
        pre = nullptr;
        int cnt;
    }
};
class Link_queue{
    private:
    int cnt;//队列结点个数
    Node *head;//头节点(队头)
    Node *tail;//尾节点(队尾)
    public:
    Link_queue(){
        cnt == 0;
        head=new Node();
        tail=head;
        head->next=head;
        head->pre=head;
    }
    ~Link_queue(){
        Node *p = head->next;
        while(p!=head){
            head->next = p->next;
            p->next->pre=head;
            delete p;
            p = head->next;
        }
        delete head;
        head = nullptr;
    }
    public:
    void push(int val){//入队
        Node *p = new Node(val);
        tail->next = p;
        p->pre = tail;
        p->next = head;
        head->pre = p;
        tail = p;
        cnt ++;
    }
    void pop(){//出队
        Node *p = head->next;
        head->next = p->next;
        p->next->pre = head;
        delete p;
        p = nullptr; 
        cnt--;
    }
    int front(){//获取第一个结点数据
        if(head->next == head){
            throw;
        }
        return head->next->data;
    }
    int back(){//获取最后一个结点数据
        if(head == tail)throw;
        return tail->data;
    }
    bool empty(){//判空
        return head->next==head;
    }
    int size(){
        return cnt;
    }
};
int main(){
    Link_queue lq1;
    lq1.push(10);
    lq1.push(20);
    cout<<lq1.front()<<endl;
    cout<<lq1.back()<<endl;
    cout<<lq1.empty()<<endl;
    lq1.pop();lq1.pop();
    
    cout<<lq1.empty()<<endl;
}