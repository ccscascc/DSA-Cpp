#include <iostream>
using namespace std;
 //双向链表
struct Node{
    int data;
    Node *pre;//指向上一个结点
    Node *next;
    Node(int Data=0)
    :data(Data)
    ,next(nullptr)
    ,pre(nullptr)
    {}
};
class DoubleLink{
private:
    Node *head;
    Node *tail;
public:
    DoubleLink(){
        head = new Node();
        tail = head;
    }
    ~DoubleLink(){
        Node *p = head;
        while(p != nullptr){
            head = head->next;
            delete p;
            p=head;
        }
    }
    void InsertHead(int val){//双向链表头插
        Node *p=new Node(val);
        p->next=head->next;
        p->pre=head;
        if(head->next!=nullptr){
            head->next->pre=p;
        }
        head->next=p;
        if(p->next==nullptr){
            tail=p;
        }
    }
    void InsertTail(int val){//双向链表尾插
        Node *p=new Node(val);
        p->pre=tail;
        tail->next=p;
        tail=p;
    }

void Erase(int val){//按值删除第一个值为val的结点
    Node *p=head->next;
    if(p==nullptr){
        cout<<"该链表为空\n";
        return;
    }
    while(p!=nullptr){
        
        if(p->data==val){
            p->pre->next=p->next;
            if(p->next!=nullptr){
                p->next->pre=p->pre;
            }
            delete p;
            return;
        }
        p=p->next;
    }
    cout<<"该链表中值为"<<val<<"的结点不存在\n";
}
void Erase_Total(int val){//按值删除所有值为val的结点
    Node *p=head;
    while(p!=nullptr){
        if(p->data==val){
            p->pre->next=p->next;
            if(p->next!=nullptr){
                p->next->pre=p->pre;
            }
           Node *next=p->next;
        delete p;
        p=next; 
        }
        else {
            p=p->next;
        }
    }
}

    void Show(){
        Node *p=head->next;
        while(p!=nullptr){
            cout<<p->data<<'\t';
            p=p->next;
        }
        cout<<endl;
    }
    void Show_Reverce(){//倒序输出
        Node *p=tail;
        while(p!=head){
            cout<<p->data<<'\t';
            p=p->pre;
        }
        cout<<endl;
    }
};

int main(){
    DoubleLink d1;
    d1.InsertHead(4);
    d1.InsertHead(5);
    d1.Show();
    d1.InsertTail(3);
    d1.InsertTail(2);
    d1.InsertTail(1);
    d1.Show();
    d1.Show_Reverce();
    d1.Erase(1);
    d1.Erase(6);
    d1.Show();
    DoubleLink d2;
    d2.Erase(1);
    d2.InsertHead(2);
    d2.InsertHead(2);
    d2.InsertHead(2);
    d2.InsertTail(1);
    d2.Show();
    d2.Erase_Total(2); 
    d2.Show();
    system("pause");
}
