#include <iostream>
#include <ctime>
#include <vector>
#include <stack>
#include <string>
using namespace std;
//排序算法实验代码
void show(int arr[]){
    int i = 0;
    while(i < 10){
        cout << arr[i++] << '\t';
    }
    cout<<endl;
}
void Buuble_sort(int arr[],int n){//冒泡排序算法 时间复杂度O(n*n); 稳定
    for(int i = 0; i < n-1; i++){
        bool flag = false;
        for(int j = 0; j < n-1-i; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = true;
            }
        }
        if(!flag)break;
    }
}
void Choose_sort(int arr[],int n){//选择排序算法 时间复杂度O(n*n);不稳定
    int min,k;                                                                                           ;
    for(int i = 0; i < n-1; i++){
        min = arr[i];//假定arr[i]是最小
        k=i;
        for(int j = i; j < n; j++){
            if(min > arr[j]){
                min = arr[j];//更新最小
                k = j;
            }
        }
        //将当前与最小调换
        arr[k] = arr[i];
        arr[i] = min;
    }
}
void Insert_sort(int arr[],int n){//插入排序 O(n*n) 稳定
    int temp = 0;
    for(int i = 1; i < n; i++){
        if(arr[i]>arr[i-1]){
            continue;
        }
        temp = arr[i];
        int j = 0;
        for(j = i - 1; j >= 0; j--){
            if(arr[j] <= temp){//若当前元素不大于temp，循环终止
                break;
            }
            else if(arr[j] > temp){//若大于，通过循环将该大于temp的位置的元素及后面的元素都向后移一位
                arr[j+1]=arr[j];
            }
        }
        arr[j+1] = temp;//并将该大于temp的位置上的元素赋值为temp
    }
}
void Insert_sort_binary(int arr[],int n){//插入排序优化————二分插入排序 复杂度 O(n*n);稳定
    //二分插入排序在找到后需要再次遍历实现插入，二分O(logn),插入O(n),整体复杂度仍是O(n*n)
    int temp = 0;
    for(int i = 1; i < n;i++){
        if(arr[i] > arr[i-1]){
            continue;
        }
        temp = arr[i];
        int j = i-1;
        int left = 0,right = j;
        while(left <= right){//二分查找
            int mid = (left + right)/2;
            if(arr[mid] > temp){
                right = mid - 1;
            }
            else if(arr[mid] <= temp){
                left = mid + 1;
            }
        }
        for(; j >= left; j--){//元素后移
            arr[j+1] = arr[j];
        }
        arr[left] = temp;
    }
}
void Shell_sort(int arr[], int n){//希尔排序 不稳定 O(n*n)
    for(int gap = n / 2; gap > 0; gap >>= 1){//设定间隔gap
        for(int i = gap; i < n; i++){
            int temp = arr[i];
            int j;
            for(j = i - gap; j >= 0 && arr[j] > temp; j -= gap){
                arr[j+gap] = arr[j];
            }
            arr[j+gap] = temp;
        }
    }
}
void Quick_sort(int arr[],int n){//快速排序 非递归
    //不稳定，时间复杂度O(n*n)
    int l = 0,r = n-1;
    stack<int>st;
    st.push(l);
    st.push(r);//利用栈的进栈出栈 模拟递归
    while(!st.empty()){
        int right = st.top();
        st.pop();
        int left = st.top();
        st.pop();
        int i = left, j = right, val = arr[(left + right) / 2];
        if(left >= right)continue;
        while(i <= j){
            while(arr[i] < val){
                i++;
            }
            while(arr[j] > val){
                j--;
            }
            if(i <= j){
            swap(arr[i++],arr[j--]);
            }
        }
        if(left < j){
            st.push(left);
            st.push(j);
        }
        if(right > i){
            st.push(i);
            st.push(right);
        }
    }
}
void Quick_sort(int arr[],int l,int r){//快速排序递归 
    //不稳定，时间复杂度最好O(n*logn)，空间复杂度O(nlogn) 递归栈开销 最坏时间空间复杂度为O(n*n) 原数据有序时最坏
    if(l >= r)return;//快速排序递归结束条件
    int i = l, j = r, val = arr[(i + j) / 2];
    while(i <= j){//对整体进行快速排序
        while(arr[i] < val){
            i++;//如果基准数左边的数小于基准数，i++,向右继续选取
        }
        while(arr[j] > val){
            j--;//如果基准数右边的数大于基准数，j--，向左继续选取
        }
        if(i <= j){//若找到基准数左边且大于基准数的数和在基准数右边且小于基准数的数，交换两数
            swap(arr[i++],arr[j--]);
        }
        //通过递归分别对基准数左，右的区域进行快速排序
        Quick_sort(arr,l,j);
        Quick_sort(arr,i,r);
    }
}
void Merge(int arr[], int l, int m, int r){//归并过程函数
    int *a = new int[r - l + 1];
    int i = l;
    int j = m + 1;
    int idx = 0;
    while(i <= m && j <= r){
        if(arr[i] <= arr[j]){
            a[idx++] = arr[i++];
        }
        else{
            a[idx++] = arr[j++];
        }
    }
    while(i <= m){
        a[idx++] = arr[i++];
    }
    while(j <= r){
        a[idx++] = arr[j++];
    }
    for(int i = l, j = 0; i <= r; i++, j++){
        arr[i] = a[j];
    }
    delete[]a;
}
void Merge_sort(int arr[], int left, int right){//归并排序递归
    if(left >= right)return;//递归结束条件
    int mid = (left + right) / 2;
    Merge_sort(arr, left, mid);
    Merge_sort(arr, mid + 1, right);//先递
    Merge(arr, left, mid, right);//后在归的过程中合并
}
void sift_down(int arr[], int i, int size){//堆排序步骤--下沉
    int val = arr[i];
    while(i < size / 2){
        int child = 2 * i + 1;
        if(child + 1 < size && arr[child + 1] > arr[child]){
            child++;
        }
        if(arr[child] > val){
            arr[i] = arr[child];
            i = child;
        }
        else break;
    }
    arr[i] = val;
}
void Heap_sort(int arr[], int size){//堆排序
    int n = size - 1;
    for(int i = (n - 1) / 2; i >= 0; i--){//从第一个非叶子结点开始，到头节点结束
        sift_down(arr, i, size);
    }
    for(int i = n; i > 0; i--){
        swap(arr[i], arr[0]);   
        sift_down(arr, 0, i);//参数3，即参与下沉的元素个数
    }
}
void Radix_sort(int arr[], int n){//基数排序（桶排序）
    int maxdata = arr[0];
    for(int i = 1; i < n; i++){
        if(maxdata < abs(arr[i])){
            maxdata = abs(arr[i]);
        }
    }
    int len = to_string(maxdata).size();
    vector<vector<int>>vecs;
    int mod = 10;
    int dev = 1;
    //将各元素按个位分配到各个桶中
    for(int i = 0; i < len; mod *= 10, dev *= 10, i++){ 
        vecs.resize(20);
        for(int j = 0; j < n; j++){
            int index = arr[j] % mod / dev + 10;
            vecs[index].push_back(arr[j]);
        }
        //遍历所有桶,按升序将所有元素拷贝回原来的数组中
        int idx = 0;
        for(auto vec : vecs){
            for(int v : vec){
                arr[idx++] = v;
            }
        }
        vecs.clear(); 
    }
}
int main(){
    srand(time(NULL));
    int arr[10];
    cout << "原数组" << endl;
    for(int i = 0; i < 10; i++){
        arr[i] = rand() % 100 + 1;
        // arr[i] = 5 - i;
    }

    show(arr);
    cout << "冒泡排序" << endl;
    Buuble_sort(arr, 10);
    show(arr);
    cout << "选择排序" << endl;
    Choose_sort(arr, 10);
    show(arr);
    cout << "插入排序" << endl;
    Insert_sort(arr, 10);
    show(arr);
    cout << "二分插入排序" << endl;
    Insert_sort_binary(arr, 10);
    show(arr);
    cout << "希尔排序" << endl;
    Shell_sort(arr, 10);
    show(arr);
    cout << "快速排序递归" << endl;
    Quick_sort(arr, 0, 9);
    show(arr);
    cout << "快速排序非递归" << endl;
    Quick_sort(arr, 10);
    show(arr);
    cout << "归并排序" << endl;
    Merge_sort(arr, 0, 9);
    show(arr);
    cout << "堆排序" << endl;
    Heap_sort(arr,10);
    show(arr);
    cout << "基数排序" << endl;
    Radix_sort(arr, 10);
    show(arr);
}
//流水落花春去也，天上人间
//十二三年就试期，五湖烟月奈相违
//春去也，飞红万点愁如海