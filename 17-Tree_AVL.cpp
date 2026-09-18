#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

class AVL{//二叉平衡搜索树
    private:
    struct Node {//结点结构体
        int data;
        Node* left;
        Node* right;
        int hight;//记录树的高度
        Node(int val = 0){
            data = val;
            left = nullptr;
            right = nullptr;
            hight = 1;
        }
    };
    Node* root;//根节点
    public:
    AVL(int val = 0) {
        root = nullptr;
    }

    private:
    int high(Node* node){//高度
        return node ? node->hight : 0;
    }

    Node* Right_Rotate(Node* node) {//右旋转
        //左孩子的左子树太高
        Node *child = node->left;
        node->left = child->right;
        child->right = node;
        //高度更新
        node->hight = max(high(node->left), high(node->right)) + 1;
        child->hight = max(high(child->left), high(child->right)) + 1;
        //node = child;
        return child;
    }
    
    Node* Left_Rotate(Node* node) {//左旋转
        //右孩子的右子树太高
        Node* child = node->right;
        node->right = child->left;
        child->left = node;
        //高度更新
        node->hight = max(high(node->left), high(node->right)) + 1;
        child->hight = max(high(child->left), high(child->right)) + 1;
        // node = child;
        return child;
    }

    Node* right_Balance(Node* node) {//右平衡操作
        //右孩子的左子树太高
        node->right = Right_Rotate(node->right);
        return Left_Rotate(node);
    }
    
    Node* left_Balance(Node* node) {//左平衡操作
        //左孩子的右子树太高
        node->left = Left_Rotate(node->left);
        return Right_Rotate(node);
    }
    
    Node* insert(Node* node, int val) {//插入递归接口
        if(node == nullptr) {
            node = new Node(val);
            return node;
        }
        if(node->data > val) {
            node->left = insert(node->left, val);
            //递归回溯时判断树是否失衡
            if(high(node->left) - high(node->right) > 1) {
                if(high(node->left->left) >= high(node->left->right)) {
                    node = Right_Rotate(node);
                }
                else {
                    node = left_Balance(node);
                }
            }
        }
        else if(node->data < val) {
            node->right = insert(node->right, val);
            if(high(node->right) - high(node->left) > 1) {
                if(high(node->right->right) >= high(node->right->left)) {
                        node = Left_Rotate(node);
                    }
                else {
                    node = right_Balance(node);
                }
            }
        }
        else if(node->data == val) {
            return node;
        }
        //插入节点后根节点的高度值需要更新
        //递归回溯时更新结点高度
        node->hight = max(high(node->left), high(node->right)) + 1;
        return node;
    }
    
    Node* erase(Node* node, int val) {//刪除
        if(node == nullptr)return nullptr;
        if(node->data > val) {
            node->left = erase(node->left, val);
            //刪除左子樹中的節點，可能導致右子樹太高而失衡
            if(high(node->right) - high(node->left) > 1) {
                if(high(node->right->right) >= high(node->right->left)) {
                    node = Left_Rotate(node);
                }
                else {
                    node = right_Balance(node);
                }
            }
        }
        else if(node->data < val) {
            node->right = erase(node->right, val);
            //刪除右子樹節點，可能導致左子樹太高而失衡
            if(high(node->left) - high(node->right) > 1) {
                if(high(node->left->left) >= high(node->left->right)) {
                    node = Right_Rotate(node);
                }
                else {
                    node = left_Balance(node);
                }
            }
        }
        else {
            if(node->left && node->right) {
                //為保證二叉樹平衡，左子樹高則刪除前驅結點，右子樹高則刪除後繼結點
                if(high(node->left) > high(node->right)) {
                    Node* pre = node->left;
                    while(pre->right) {
                        pre = pre->right;
                    }
                    node->data = pre->data;
                    node->left = erase(node->left, pre->data);
                }
                else {
                    Node* pre = node->right;
                    while(pre->left) {
                        pre = pre->left;
                    }
                    node->data = pre->data;
                    node->right = erase(node->right, pre->data);
                }
            }
            else if(node->left) {
                Node *pre = node->left;
                delete node;
                return pre;
            }
            else if(node->right) {
                Node *pre = node->right;
                delete node;
                return pre;
            }
            else {
                return nullptr;
            }
        }
        return node;
        node->hight = max(high(node->left), high(node->right)) + 1;
    }

    void inorder(Node *root) {//中序遍历——递归写法
        if(!root)return;
        inorder(root->left);
        cout << root->data <<'\t';
        inorder(root->right);
    }

    void preorder(Node* node) {//前序遍历——递归写法
        if(!node)return;
        cout << node->data;
        preorder(node->left);
        preorder(node->right);
    }
    public:
    void insert(int val) {//插入递归调用
        root = insert(root, val);
    }
    
    void inorder() {//递归中序遍历调用
        cout << "中序遍历(递归)：";
        inorder(root);
        cout << endl;
    }
    void preorder() {//递归前序遍历调用
        cout << "前序遍历(递归)：";
        preorder(root);
        cout << endl;
    }
    void erase(int val){//刪除操作调用
        root = erase(root, val);
    }
};
int main(){
    AVL avl;
    for(int i = 1; i <= 10; i++) {
        avl.insert(i);
    }
    avl.inorder();
    avl.erase(4);
    avl.inorder();
    return 0;
}
