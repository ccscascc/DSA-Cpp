#include <iostream>
#include <functional>
#include <ctime>
#include <cstring>
using namespace std;

//基于堆的优先级队列
class priority_queue {
public:
    using Comp = function<bool(int, int)>;
private:
    int* que;
    int size_;//数组元素个数
    int cap;//数组容量
    Comp comp;//比较器对象
public:
    priority_queue(int size = 20, Comp c = greater<int>()) {
        size_ = 0;
        cap = size;
        comp = c;
        que = new int[cap];
    }
    ~priority_queue() {
        delete[]que;
        que = nullptr;
    }
    void push(int val) {//入堆
        if (size_ == cap) {
            int* p = new int[2 * cap];
            memcpy(p, que, sizeof(int) * cap);
            delete[]que;
            que = p;
            cap *= 2;
        }
        if (size_ == 0) {//堆为空
            que[size_] = val;
        }
        else {//堆不为空
            Sift_up(size_, val);//进行上浮操作，在合适的位置插入val
        }
        size_++;
    }
    void pop() {
        if (size_ == 0)throw;
        size_--;
        if (this->size_ > 0) {
            //删除堆顶的元素后还有剩余的元素，进行下沉操作
            Sift_down(0, que[size_]);
        }
        
    }
    int empty() {
        return size_ == 0;
    }
    int size() {
        return this->size_;
    }
    int top() {
        if (size_ == 0)throw;
        return que[0];
    }
private:
    void Sift_up(int i, int val) {//上浮操作
        while (i > 0) {//最多计算到根节点即下标为0的位置
            int father = (i - 1) / 2;
            if (comp(val, que[father])) {//若val大于相应父节点的值
                que[i] = que[father];//给该子结点赋值为val
                i = father;//更新i的值，继续向上寻找
            }
            else {
                break;//若已找到父结点的值大于val，循环终止
            }
        }
        que[i] = val;//将val填入空缺中
    }
    void Sift_down(int i, int val) {//下沉操作
        while (i < size_ / 2) {//i下沉不能超过最后一个有子节点的结点
            int child = 2 * i + 1;
            if (child + 1 < size_ && comp(que[child + 1], que[child])) {
                child++;//若右孩子存在且右孩子值大于左孩子，将左孩子更新为右孩子
            }
            if (comp(que[child], val)) {
                que[i] = que[child];
                i = child;
            }
            else{
                break;
            }
        }
        que[i] = val;
    }
    //上浮、下沉操作时间复杂度均为 O(n);
};
int main() {
    srand(time(NULL));
    priority_queue pq1;
    for(int i = 0; i < 10; i++){
        pq1.push(rand()%100+1);
    }
    while(!pq1.empty()){
        cout << pq1.top() << "  ";
        pq1.pop();
    }
    cout << endl;
}
