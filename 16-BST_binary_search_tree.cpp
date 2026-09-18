#include <iostream>
#include <functional>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;
//BST二叉搜索树

template<typename T, typename Compare = less<T>>
class BST{
    private:
    Compare comp;
    struct Node{
        T data;
        Node *left;
        Node *right;
        Node(T val){
            data = val;
            left = nullptr;
            right = nullptr;
        }
    };
    Node *root;//指向BST根结点
    public:
    BST(){
        root = nullptr;
    }
    ~BST(){//利用层序遍历释放BST内存
        queue<Node*>que;
        if(root!=nullptr){
            que.push(root);
            while(!que.empty()){
                Node *front = que.front();
                que.pop();
                if(front->left != nullptr){
                    que.push(front->left);
                }
                if(front->right != nullptr){
                    que.push(front->right);
                }
                delete front;
            }
        }
    }
    public:
    void insert(T val){//插入(非递归)
        if(root == nullptr){//树为空，新建根节点即插入位置
            root = new Node(val);
            return;
        }
        Node *parent = nullptr;//cur节点的父结点（当前为nullptr）
        Node *cur = root;
        //搜索合适的插入位置
        while(cur != nullptr){
            if(!comp(cur->data, val) && val != cur->data){//cur->data > val
                parent = cur;
                cur = cur->left;
            }
            else if(comp(cur->data, val)){
                parent = cur;
                cur = cur->right;
            }
            else return;//不插入相等的元素
        }
        cur = new Node(val);
        if(comp(val, parent->data)){
            parent->left = cur;
        }
        else parent->right = cur;
    }
    Node* Insert(Node *node, const T&val){
        if(node == nullptr){
            //递归结束，找到插入val的位置
            return new Node(val);
        }
        if(node->data == val)return node;
        else if(comp(node->data, val)){
            node->right = Insert(node->right, val);
        }
        else {
            node->left = Insert(node->left, val);
        }
        return node;
    }
    void Insert(T val){//插入（递归）调用
        root = Insert(root, val);
    }
    bool find(T val){//查找（非递归）
        Node *cur = root;
        if(cur == nullptr){
            return false;
        }
        while(cur != nullptr){
            if(comp(cur->data, val)){
                cur = cur->right;
            }
            else if(cur->data != val){
                cur = cur ->left;
            }
            else{
                return true;
            }
        }
        return false;
    }
    bool Find(Node *node, const T& val){//查找递归实现
        if(node == nullptr)return false;
        if(node->data == val)return true;
        else if(!comp(node->data, val)){
            return Find(node->left, val);
        }
        else return Find(node->right, val);
    }
    bool Find(T val){//查找（递归）调用
        return Find(root, val);
    }
    void erase(int val){//删除（非递归）
        if(!find(val))return;//如果待删除结点不存在，直接return
        Node *parent = nullptr;
        Node *cur = root;
        while(cur != nullptr){
            if(comp(cur->data, val)){
                parent = cur;
                cur = cur->right;
            }
            else if(cur->data != val){
                parent = cur;
                cur = cur->left;
            }
            else{
                break;//找到待删除的结点
            }
        }
        if(cur->left != nullptr && cur->right != nullptr){
            Node *pre = cur->left;
            parent = cur;
            //找以cur为根节点的前驱节点
            while(pre->right != nullptr){
                parent = pre;
                pre = pre->right;
            }
            cur->data = pre->data;
            cur = pre;
        }
        Node *child = cur->left;
        if(child == nullptr){
            child = cur->right;
        }
        if(parent->left == cur){
            parent->left = child;
        }
        else{
            parent->right = child;
        }
        delete cur;
    }
    Node* Erase(Node *node, int val) {//删除（递归）实现
        if(node == nullptr)return nullptr;
        if(node->data == val){//找到待删除结点
            if(node->left != nullptr && node->right != nullptr){
                Node *pre = node->left;//找前驱节点
                while(pre->right != nullptr) {
                    pre = pre->right;
                }
                node->data = pre->data;
                //通过递归删除前驱节点
                node->left = Erase(node->left, pre->data);
            }
            else if(node->left == nullptr) {//待删结点的左子节点为空，返回右子节点，delete node
                Node *p = node->left;
                delete node;
                return p;
            }
            else if(node->right == nullptr) {//待删结点的右子节点为空，返回左子节点，delete node
                Node *p = node->right;
                delete node;
                return p;
            }
            else {//待删结点为叶子节点，直接delete node ，返回nullptr
                delete node;
                return nullptr;
            }
        }
        if(comp(node->data, val)) {
            node->right = Erase(node->right, val);
        }
        if(comp(val, node->data)) {
            node->left = Erase(node->left, val);
        }
        return node;//返回当前结点到父结点，更新地址域
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    void Erase(int val) {//删除（递归）调用
        root = Erase(root, val);
    }
    void preorder(Node *root) {//前序遍历——递归写法
        if(root == nullptr)return;
        cout << root->data <<'\t';
        preorder(root->left);
        preorder(root->right);
    }
    void preorder() {//递归前序遍历调用
        cout << "前序遍历(递归):";
        preorder(root);
        cout << endl;
    }
    void Preorder() {//前序遍历——非递归写法
        //利用栈出栈入栈的先后顺序实现二叉树的迭代前序遍历
        cout << "前序遍历(非递归):";
        if(root == nullptr){
            return;
        }
        stack<Node*>st;
        st.push(root);
        while(!st.empty()) {
            Node *p = st.top();
            st.pop();
            cout << p->data << '\t';
            if(p->right != nullptr) {//右节点先入栈，后出栈
                st.push(p->right);
            }
            if(p->left != nullptr) {
                st.push(p->left);
            }
        }
        cout << endl;
    }
    void inorder(Node *root) {//中序遍历——递归写法
        if(!root)return;
        inorder(root->left);
        cout << root->data <<'\t';
        inorder(root->right);
        
    }
    void inorder() {//递归中序遍历调用
        cout << "中序遍历(递归):";
        inorder(root);
        cout << endl;
    }
    void Inorder() {//中序遍历——非递归写法
        cout << "中序遍历(非递归):";
        if(root == nullptr)return;
        stack<Node*>st;
        Node *cur = root;
        while(cur != nullptr) {//先依次入栈左节点
            st.push(cur);
            cur = cur->left;
        }
        while(!st.empty()) {
            Node *p = st.top();
            st.pop();
            cout << p->data << '\t';//出栈并输出左叶子节点或没有左子节点的父结点
            cur = p->right;
            while(cur != nullptr) {//将根节点的右子树入栈
                st.push(cur);
                cur = cur->left;
            }
        }
        cout << endl;
    }
    void postorder(Node *root) {//后序遍历——递归写法
        if(!root)return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data <<'\t';
        
    }
    void postorder() {//递归后序遍历调用
        cout << "后序遍历(递归):";
        postorder(root);
        cout << endl;
    }
    void Postorder() {//后序遍历——非递归写法
        //用两个栈
        cout << "后序遍历(非递归):";
        if(root == nullptr)return;
        Node *cur = root;
        stack<Node*>st1;
        stack<Node*>st2;
        st1.push(root);
        while(!st1.empty()) {
            Node *p = st1.top();
            st1.pop();
            st2.push(p);
            if(p->left != nullptr) {
                st1.push(p->left);
            }
            if(p->right != nullptr) {
                st1.push(p->right);
            }
        }
        while(!st2.empty()) {
            cout << st2.top()->data << '\t';
            st2.pop();
        }
        cout << endl;
    }
    int high(Node *node) {//统计二叉树层数
        if(!node)return 0;
        int l = high(node->left);
        int r = high(node->right);
        return max(l,r) + 1;
    }
    int number(Node *node) {//统计结点个数
        int num = 0;
        if(!node)return 0;
        if(node->left == nullptr && node->right == nullptr){
            return 1;
        }
        num += number(node->left);
        num += number(node->right);
        return num + 1;
    }
    int getNumber() {
        return number(root);
    }
    int getHigh() {
        return high(root);
    }
    void getRow(Node *node, int high, vector<int>&res){
        if(!node)return;
        if(high == 1) {
            res.push_back(node->data);
            return;
        }
        getRow(node->left, high - 1, res);
        getRow(node->right, high - 1, res);
    }
    vector<vector<int>> LevelOrder(Node *node) {//层序遍历——递归
        int h = high(node);
        vector<vector<int>>ans;
        for(int i = 0; i < h; i++){
            vector<int>row;
            getRow(node, i + 1, row);
            ans.push_back(row);
        }
        return ans;
    }
    void levelOrder() {
        vector<vector<int>>ans(LevelOrder(root));
        cout << "层序遍历(分层)(递归):" << endl;
        int cnt = 1;
        for(auto x : ans) {
            cout << "第" << cnt++ << "层:";
            for(auto y : x){
                cout << y << '\t';
            }
            cout << endl;
        }
    }
    void LevelOrder() {//层序遍历——非递归
        //广度遍历，利用队列
        cout << "层序遍历(分层)(非递归):" << endl;
        if(root == nullptr){
            return;
        }
        int x = 0;
        queue<Node*>que;
        que.push(root);
        while(!que.empty()) {
            int s = que.size();
            cout << "第" << ++x << "层:";
            for(int i = 0; i < s; i++){
                
                Node *front = que.front();
                que.pop();
                cout << front->data << '\t';
                if(front->left != nullptr){
                    que.push(front->left);
                }
                if(front->right != nullptr){
                    que.push(front->right);
                }  
            }
            cout << endl;
        }
    }
    Node* rebulid_(vector<int>& preorder, int i, int j, vector<int>& inorder, int m, int n){//根据中序遍历和前序遍历构建二叉树
        //由前序遍历知道二叉树的根节点，由中序遍历知道二叉树根节点左右的结点有哪些
        if(i > j || m > n){
            return nullptr;
        }
        Node* node = new Node(preorder[i]);//前序遍历的第一个即根节点，将此作为子树的根节点
        for(int k = m; k <= n; k++){
            if(preorder[i] == inorder[k])//在中序遍历中找子树根节点的下标 k
            {
                node->left = rebulid_(preorder, i + 1, k - m + i, inorder, m, k - 1);//根节点的左子树包含
                node->right = rebulid_(preorder, i + k - m + 1, j,inorder, k + 1, n);//根节点的右子树包含
                return node;
            }
        }

        return node;
    }
    void rebulid(vector<int>& preorder, int i, int j, vector<int>& inorder, int m, int n){
        
        root = rebulid_(preorder, i, j, inorder, m, n);
    }
};
void test01(){//测试根据中序和前序构建二叉树
    vector<int>pre(11),in(11);
    pre = {58,24,0,5,34,41,67,62,64,69,78};
    in = {0,5,24,34,41,58,62,64,67,69,78};
    BST<int> bst;
    bst.rebulid(pre, 0, 10, in, 0, 10);
    bst.preorder();
    bst.inorder();
}
int main(){
    int arr[] = {10,2,32,4,9};
    BST<int> bst1;
    for(int v : arr){
        bst1.insert(v);
    }
    cout << "--------------------------------------------------------\n";
    bst1.insert(12);
    cout << bst1.find(12) << endl;
    bst1.erase(12);
    bst1.preorder();
    bst1.inorder();
    bst1.postorder();
    bst1.levelOrder();
    cout << "--------------------------------------------------------\n";

    BST<int> bst2;
    for(int v : arr){
        bst2.Insert(v);
    }
    bst2.Preorder();
    bst2.Inorder();
    bst2.postorder();
    bst2.LevelOrder();
    bst2.Insert(12);
    //cout << bst2.Find(12);
    bst2.Erase(12);
    bst2.Erase(10);
    //cout << bst2.Find(12) << endl;
    cout << "\n--------------------------------------------------------\n";
    test01();
    return 0;
}
//2026--6--2