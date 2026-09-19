#include <climits>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
// 单向循环链表代码
struct Node{
    Node(int data=0):Data(data),Next(nullptr){}
    int Data;
    Node *Next;
};
class CircleLink{
    private:
    Node *head;
    Node *tail;

    public:
    CircleLink(){
        head=new Node();
        tail=head;
        head->Next=head;
    }
    ~CircleLink(){
        Node *p=head->Next;
        while(p!=head){
            head->Next=p->Next;
            delete p;
            p=head->Next;
        }       
        delete head;
    }
    void InsertTail(int val){//单向循环链表尾插法(时间复杂度O(1) )
        Node *node=new Node(val);
        node->Next=tail->Next;
        tail->Next=node;
        tail=node;
    }
    void InsertHead(int val){//单向循环链表头插法
        Node *node=new Node(val);
        node->Next=head->Next;
        head->Next=node;
        if(node->Next==head){
            tail=node;
        }
    }
    void Show(){
        Node *p;
        for(p=head->Next;p!=head;p=p->Next){
            cout<<p->Data<<'\t';
        }
        cout<<endl;
    }
};
void Josper(Node *head,int n,int k){//约瑟夫环问题
    Node *p=head;
    Node *q=head;
    for(int i=1;i<k;i++){
        q=p;
        p=p->Next;
    }
    for(;;){
        for(int i=1;i<n;i++){
            q=p;
            p=p->Next;
        }
        if(p==q){
            cout<<p->Data<<'\t';
            delete p;
            break;
        }
        
        cout<<p->Data<<'\t';
        q->Next=p->Next;
        delete p;
        p=q->Next;
    }
    cout<<endl;
}
int main(){
    {
        Node *head=new Node(1);
        Node *n1=new Node(2);
        Node *n2=new Node(3);
        Node *n3=new Node(4);
        Node *n4=new Node(5);
        Node *n5=new Node(6);
        Node *n6=new Node(7);
        Node *n7=new Node(8);
        head->Next=n1;
        n1->Next=n2;
        n2->Next=n3;
        n3->Next=n4;
        n4->Next=n5;
        n5->Next=n6;
        n6->Next=head;
        // n6->Next=n7;
        // n7->Next=head;
        Josper(head,7,4);//
    }
    system("pause");
    return 0;
}
