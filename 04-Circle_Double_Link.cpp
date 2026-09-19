#include <iostream>
using namespace std;
//s双向循环链表
struct Node{
    int data;
    Node *next;
    Node *pre;
    Node(int val=0):data(val),next(nullptr),pre(nullptr){}
};

class Circle_Double_Link{
    private:
    Node *head;
    Node *tail;
    public:
    Circle_Double_Link(){
        head=new Node();
        tail=head;
        head->next=head;
        head->pre=head;
    }
    ~Circle_Double_Link(){
        Node *p=head->next;
        while(p!=head){
            head->next=p->next;
            p->next->pre=head;
            delete p;
            p=head->next;
        }
        delete head;
        head=nullptr;
    }
    void InsertHead(int val){
        Node *p=new Node(val);
        p->next=head->next;
        p->pre=head;
        head->next=p;
        if(p->next=head){
            tail=p;
        }

    }
    void show(){
        Node *p=head->next;
        while(p!=head){
            cout<<p->data<<'\t';
            p=p->next;
        }
        cout<<endl;
    }
};

int main(){
    Circle_Double_Link c1;
    c1.InsertHead(2);
    c1.show();
}
