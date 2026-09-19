#include <limits.h>
#include <climits>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
//单向链表实验代码
struct Node{
    Node(int data = 0) : Data(data), Next(nullptr) {}
    int Data;
    Node *Next;
};
class Click{
public:
    Node *head;
    Node *tail;

public:
    Click() {
        head = new Node(); // head 头节点
        tail = head;       // tail指向尾节点，初始为head
    }

    ~Click() {
        Node *p = head;
        while (p != nullptr)
        {
            Node *temp = p;
            p = p->Next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }
    void inserttail(int val)
    {
        Node *newnode = new Node(val);
        Node *p = head;
        while (p->Next != nullptr)
        {
            p = p->Next;
        }
        p->Next = newnode;
    }
    void InsertTail(int val)
    {                                  // 单链表尾插法，利用tail尾节点实现时间复杂度O(1)
        Node *newnode = new Node(val); //
        tail->Next = newnode;          //
        tail = newnode;
    }
    void InsertHead(int val)
    { // 头插法
        Node *node = new Node(val);
        node->Next = head->Next;
        head->Next = node;
    }
    void Del(int val)
    { // 按值删除首个值为结点
        Node *p = head->Next;
        Node *pre = head;
        while (p != nullptr)
        {
            if (p->Data == val)
            {
                pre->Next = p->Next;
                p->Next = nullptr;
                delete p; // 防止空指针
                return;
            }
            else
            {
                p = p->Next;
                pre = pre->Next;
            }
        }
    }
    void DelTotal(int val)
    { // 按值删除所有值为val的结点
        Node *p = head->Next;
        Node *pre = head;
        while (p != nullptr)
        {
            if (p->Data == val)
            {
                pre->Next = p->Next;
                Node *temp = p;
                p = p->Next;
                delete temp;
            }
            else
            {
                p = p->Next;
                pre = pre->Next;
            }
        }
    }
    void DelTotal1(int val)
    { // 按值删除所有值为val的结点
        Node *p = head->Next;
        Node *pre = head;
        while (p != nullptr)
        {
            if (p->Data == val)
            {
                pre->Next = p->Next;
                delete p;
                p = pre->Next;
            }
            else
            {
                p = p->Next;
                pre = pre->Next;
            }
        }
    }
    bool Find(int val)
    { // 判断是否存在值为val的结点
        Node *p = head->Next;
        while (p != nullptr)
        {
            if (p->Data == val)
            {
                return true;
            }
            else
                p = p->Next;
        }
        return false;
    }
    int Count(int val)
    {
        int count = 0;
        Node *p = head->Next;
        while (p != nullptr)
        {
            if (p->Data == val)
                count++;
            p = p->Next;
        }
        return count;
    }
    friend void Reverse(Click &lick);
    friend int GetLast(Click &lick, int k);
    friend void MergeList(Click &lick1, Click &lick2);
    friend void MergeList_new(Click &lick1, Click &lick2, Click &lick);
    friend bool Judge_Circle(Node *head, int &val);
    friend bool Judge_Intersert(Node *node1, Node *node2, int &val);
    void Show()
    {
        Node *p = head->Next;
        while (p != nullptr)
        {
            cout << p->Data << '\t';
            p = p->Next;
        }
        cout << endl;
    }
};
void Reverse(Click &lick)
{ //  依次修改每个结点的指针方向，例如：1->2->3 => 1<-2 3 => 1<-2<-3 最终实现链表的反转
    Node *p = lick.head->Next; // 要实现反转的结点
    if (p == nullptr)
        return;
    lick.head->Next = nullptr; // 要反转结点的前一个，在反转后指向这个结点
    while (p != nullptr)
    {
        Node *q = p->Next; // 保存要反转结点的下一个结点
        p->Next = lick.head->Next; // 反转指针
        lick.head->Next = p;
        p = q; // p,q都指向原本链表的下一个结点
    }
    lick.tail = lick.head; // 维护尾节点
    while (lick.tail->Next != nullptr)
    {
        lick.tail = lick.tail->Next;
    }
}
int GetLast(Click &lick, int k)
{ // 获取链表倒数第K个结点
    Node *p = lick.head->Next;
    Node *q = lick.head->Next;
    int n = 0;
    while (n != k && p != nullptr)
    {
        p = p->Next;
        n++;
    }
    if (n < k)
        return INT_MAX;
    while (p != nullptr)
    {
        p = p->Next;
        q = q->Next;
    }
    return q ? q->Data : INT_MAX;
}
void MergeList(Click &lick1, Click &lick2)
{ // 合并两个有序链表，结果有序
    Node *p = lick1.head->Next;
    Node *q = lick2.head->Next;
    Node *last = lick1.head;
    lick2.head->Next = nullptr;
    while (p && q)
    {
        if (q->Data < p->Data)
        {
            last->Next = q;
            q = q->Next;
            last = last->Next;
        }
        else
        {
            last->Next = p;
            p = p->Next;
            last = last->Next;
        }
    }
    if (p != nullptr)
        last->Next = p;
    if (q != nullptr)
        last->Next = q;
}
void MergeList_new(Click &lick1, Click &lick2, Click &lick)
{ // 合并两个有序链表，将合并结果存在新链表中，新链表有序
    Node *p = lick1.head->Next;
    Node *q = lick2.head->Next;
    Node *r = lick.head;
    while (p && q)
    {
        if (p->Data < q->Data)
        {
            r->Next = new Node(p->Data);
            p = p->Next;
            r = r->Next;
        }
        else
        {
            r->Next = new Node(q->Data);
            q = q->Next;
            r = r->Next;
        }
    }
    while (p)
    {
        r->Next = new Node(p->Data);
        p = p->Next;
        r = r->Next;
    }
    while (q)
    {
        r->Next = new Node(q->Data);
        q = q->Next;
        r = r->Next;
    }
}
bool Judge_Circle(Node *head, int &val)
{ // 判断链表是否成环，若成环，将val赋值为环的入口的前一个结点的值
    Node *fast = head;
    Node *slow = head;
    while (fast != nullptr && fast->Next != nullptr)
    {
        fast = fast->Next->Next;
        slow = slow->Next;
        if (fast == slow)
        {
            fast = head;
            while (fast != slow)
            {
                slow = slow->Next;
                fast = fast->Next;
            }
            if (fast == slow)
                val = slow->Data;
            return true;
        }
    }
    return false;
}
bool Judge_Intersert(Node *node1, Node *node2, int &val)
{ // 判断两链表是否相交，若相交，将val赋值为相交结点的值
    Node *p = node1;
    Node *q = node2;
    int cur = 0, length_1 = 0, length_2 = 0;
    while (p != nullptr)
    {
        p = p->Next;
        length_1++;
    }
    while (q != nullptr)
    {
        q = q->Next;
        length_2++;
    }
    cur = length_1 - length_2;
    p = node1;
    q = node2;
    if (cur > 0)
    {
        while (cur-- > 0)
        {
            p = p->Next;
        }
        while (p != nullptr && q != nullptr)
        {

            if (p == q)
            {
                val = p->Data;
                return true;
            }
            p = p->Next;
            q = q->Next;
        }
    }
    else
    {
        while (cur++ < 0)
        {
            q = q->Next;
        }
        while (p != nullptr && q != nullptr)
        {

            if (p == q)
            {
                val = p->Data;
                return true;
            }
            p = p->Next;
            q = q->Next;
        }
    }
    return false;
}
int main()
{
    Click c;
    c.InsertTail(10);
    c.InsertTail(20);
    c.InsertTail(10);
    c.InsertTail(40);
    c.InsertHead(20);
    c.inserttail(10);
    c.Show();
    c.Del(10);
    c.Show();
    c.DelTotal(10);
    c.Show();
    c.DelTotal(20);
    c.Show();
    cout << c.Find(40) << endl;
    cout << c.Find(10) << endl;
    c.InsertTail(10);
    c.InsertTail(10);
    c.InsertTail(1);
    c.Show();
    cout << c.Count(10) << endl;
    Reverse(c);
    c.Show();
    c.InsertTail(5);
    c.InsertHead(2);
    c.InsertTail(8);
    c.Show();
    cout << GetLast(c, 3) << endl;
    cout << GetLast(c, 7) << endl;
    // cout<<LLONG_MAX<<endl;
    Click c1;
    for (int i = 1; i <= 5; i++, c1.InsertTail(i))
        ;
    Click c2;
    for (int i = 0; i < 5; i++, c2.InsertTail(i))
        ;
    c1.Show();
    c2.Show();
    Click c3;
    MergeList_new(c1, c2, c3);
    c3.Show();
    MergeList(c1, c2);
    c1.Show();
    {
        Node head;
        Node *n1 = new Node(10);
        Node *n2 = new Node(15);
        Node *n3 = new Node(20);
        Node *n4 = new Node(25);
        head.Next = n1;
        n1->Next = n2;
        n2->Next = n3;
        n3->Next = n4;
        n4->Next = n2;
        int val = 0;
        cout << Judge_Circle(&head, val) << endl;
        cout << val << endl;
    }
    Node head;
    Node *n1 = new Node(10);
    Node *n2 = new Node(15);
    Node *n3 = new Node(20);
    Node *n4 = new Node(25);
    head.Next = n1;
    n1->Next = n2;
    n2->Next = n3;
    n3->Next = n4;
    Node head_1;
    Node n5(10);
    Node *n6 = new Node(15);
    Node *n7 = new Node(20);
    // Node *n8 = new Node(25);
    head_1.Next = &n5;
    n5.Next = n6;
    n6->Next = n7;
    n7->Next = n3;
    int val_1 = 0;
    cout << Judge_Intersert(&head, &head_1, val_1) << endl;
    cout << val_1 << endl;
    int val_2 = 0;
    cout << val_2 << endl;
}
