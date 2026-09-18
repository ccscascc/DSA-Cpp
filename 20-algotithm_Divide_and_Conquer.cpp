#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>

using namespace std;
//分治算法实验代码

// T1. 二分搜索
bool Binary_search(vector<int>& arr, int target){ //分治算法--二分搜索
    int n = arr.size();
    int left = 0, right = n - 1;
    sort(arr.begin(), arr.end());
    while(right >= left) {
        int  mid = (left + right) / 2;
        if(arr[mid] == target)return true;
        else if(arr[mid] < target) {
            left = mid + 1;
        }
       else right = mid - 1;
    }
    return false;
}
void test_binary_search(){//二分搜索测试
    vector<int> arr;
    for(int i = 0; i < 10; i++) {
        int temp = rand() % 31;
        arr.push_back(temp);
        cout << temp << " ";
    }
    cout << endl;
    int target = 10;
    // cout << "输入查找的数字:";
    // cin >> target;
    if(Binary_search(arr, target)) {
        cout << target << "存在" << endl;
    }
    else cout << target << "不存在" << endl;
}

void fast_sort(vector<int>& arr, int left, int right){ //分治算法--快速排序
    if(left >= right) return;
    int i = left, j = right;
    int val = arr[left];
    while(i < j) {
        while(arr[i] < val && i < j) i++;
        while(arr[j] > val && i < j) j--;
        if(i <= j) swap(arr[i++], arr[j--]);
    }
    fast_sort(arr, left, j);
    fast_sort(arr, i, right);
}
void test_fast_sort() { //快速排序测试
    vector<int>arr;
    cout << "原数组元素:";
    for(int i = 0; i < 10; i++) {
        int temp = rand() % 31;
        arr.push_back(temp);
        cout << temp << " ";
    }
    cout << endl;
    fast_sort(arr, 0, arr.size() - 1);
    cout << "快排后元素:";
    for(int num : arr) cout << num << " ";
    cout << endl;
}

// T2. 快排分割求解 topk 问题
int position(vector<int>& arr, int left, int right) { //确定基准数位置
    int i = left, j = right, val = arr[left];
    while(i < j) {
        while(i < j && arr[j] <= val) {
            j--;
        }
        while(i < j && arr[i] >= val) {
            i++;
        }
        if(i < j) {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[left]);
    return i;
}
int max_topk_quick_sort(vector<int>& arr, int left, int right, int k) {//第k大
    int pos = position(arr, left, right);
    if(pos == k - 1) return arr[pos];
    else if(pos > k - 1) return max_topk_quick_sort(arr, left, pos - 1, k);
    else return max_topk_quick_sort(arr, pos + 1, right, k);
}
int min_topk_quick_sort(vector<int>& arr, int left, int right, int k) {//第k小
    int pos = position(arr, left, right);
    if(pos == arr.size() - k) {
        return arr[pos];
    }
    else if(pos < arr.size() - k) {
        return min_topk_quick_sort(arr, pos + 1, right, k);
    }
    else return min_topk_quick_sort(arr, left, pos - 1, k);
}
void test_topk_quick_sort() { //快排分割求解topk测试
    vector<int>arr;
    cout << "原数组元素:";
    for(int i = 0; i < 10; i++) {
        int temp = rand() % 40;
        arr.push_back(temp);
        cout << temp << " ";
    }
    cout << endl;
    int k = 3;
    vector<int> arr1(arr), arr2(arr);
    cout << "大top" << k << "元素:";
    cout << max_topk_quick_sort(arr1, 0, arr1.size() - 1, k) << endl;
    cout << "小top" << k << "元素:";
    cout << min_topk_quick_sort(arr2, 0, arr2.size() - 1, k) << endl;
    cout << "排序后数组:";
    sort(arr.begin(), arr.end(), greater<int>());
    for(int num : arr) cout << num <<" ";
    cout << endl;
    // vector<int>res = {1,1};
    // cout << max_topk_quick_sort(res, 0, 1, 1) << endl;
}

// T3. 归并排序
void merge(vector<int>& arr, int left, int right, int mid) {
    vector<int> temp;// 额外的辅助空间，存储合并子问题的数组
    temp.reserve(right - left + 1);
    int i = left;
    int j = mid + 1;
    int idx = 0;
    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        }
        else {
            temp.push_back(arr[j++]);
        }
    }
    while(i <= mid) {
        temp.push_back(arr[i++]);
    }
    while(j <= right) {
        temp.push_back(arr[j++]);
    }
    for(i = left, j = 0; i <= right; i++, j++) { //temp数组中元素存入arr中
        arr[i] = temp[j];
    }
}
void merge_sort(vector<int>& arr, int left, int right) { // 归并排序
    //-----------------------------------------------------------------
    // 分治过程--划分子问题，将数组分为只有一个元素的数组，此时数组可视为有序
    int mid = (left + right) / 2;
    if(left >= right) return;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    //-----------------------------------------------------------------
    //向上合并过程中，得到子问题的解
    merge(arr, left, right, mid);
}
void test_merge_sort() {//归并排序测试
    vector<int> arr;
    
    cout << "原数组元素:";
    for(int i = 0; i < 10; i++) {
        arr.push_back(rand() % 20);
        cout << arr[i] << " ";
    }
    cout << endl;
    merge_sort(arr, 0, 10);
    cout << "排序后元素:";
    for(int a : arr) {
        cout << a << " ";
    }
    cout << endl;
}

// T4. 合并 K 个有序单链表问题
struct ListNode {//单链表结点
    int val;
    ListNode* next;
    ListNode(int val = 0) {
        this->val = val;
        next = nullptr;
    }
};
ListNode* init_list(initializer_list<int> list){ // 创建新链表
    ListNode *head = nullptr;
    ListNode *p = nullptr;
    for(int v : list) {
        if(!head) {
            head = new ListNode(v);
            p = head;
        }
        else {
            p->next = new ListNode(v);
            p = p->next;
        }
    }
    return head;
}
ListNode* mergelist_2(ListNode* left, ListNode* right) { // 合并两个有序链表
    ListNode *p1 = left, *p2 = right;
    if(!p1)return p2;
    if(!p2)return p1; 
    ListNode* res = new ListNode();
    ListNode *pre = res;
    while(p1 && p2) {
        if(p1->val <= p2->val) {
            pre->next = new ListNode(p1->val);
            p1 = p1->next;
        }
        else {
            pre->next = new ListNode(p2->val);
            p2 = p2->next;
        }
        pre = pre->next;
    }
    if(p1) pre->next = p1;
    else if(p2) pre->next = p2;
    return res->next;
}
ListNode* mergelist_k(vector<ListNode*>& list_arr, int left, int right) { // 合并 K 个有序单链表
    if(left >= right) return list_arr[left];
    int mid = (left + right) / 2;
    ListNode* l = mergelist_k(list_arr, left, mid);
    ListNode* r = mergelist_k(list_arr, mid + 1, right);
    return mergelist_2(l, r);// 将问题转化为合并两个链表
}
void test_mergelist_k() { // 合并 K 个有序单链表 测试
    ListNode* p1 = init_list({1, 3, 5, 7, 9});
    ListNode* p2 = init_list({0, 2, 4, 6, 8});
    ListNode* p3 = init_list({1, 4, 6, 9, 10});
    vector<ListNode*>list_arr({p1, p2, p3});
    int cnt = 1;
    cout << "链表" << cnt++ << "元素:";
    for(ListNode *p = p1; p != nullptr; p = p->next) {
        cout << p->val << " ";
    }
    cout << endl;
    cout << "链表" << cnt++ << "元素:";
    for(ListNode *p = p2; p != nullptr; p = p->next) {
        cout << p->val << " ";
    }
    cout << endl;
    cout << "链表" << cnt++ << "元素:";
    for(ListNode *p = p3; p != nullptr; p = p->next) {
        cout << p->val << " ";
    }
    cout << endl;
    ListNode* res = mergelist_k(list_arr, 0, list_arr.size() - 1);
    cout << "合并后的链表:";
    for(ListNode *p = res; p != nullptr; p = p->next) {
        cout << p->val << " ";
    }
    cout << endl;
}

// T5. O(log(m + n)) 时间复杂度求两个有序数组的的中位数
double midval(vector<int>& arr1, vector<int>& arr2) {
    int len1 = arr1.size(), len2 = arr2.size();
    if(arr1.empty()) {
        return len2 % 2 ? arr2[len2 / 2] : (arr2[len2 / 2] + arr2[len2 / 2 - 1]) * 1.0 / 2;
    }
    else if(arr2.empty()) {
        return len1 % 2 ? arr1[len1 / 2] : (arr1[len1 / 2] + arr1[len1 / 2 - 1]) * 1.0 / 2;
    }
    if(len1 > len2) { // 在短的数组中求解i，j值
        return midval(arr2, arr1);
    }
    int i = 0, j = 0;
    int begin = 0, end = len1;
    int k = (len1 + len2 + 1) / 2; // +1 保证是中位数 // k是第k个元素，不是下标为k

    //中位数所在的下标（i或j）需满足 arr1[i] > arr2[j - 1] && arr2[j] > arr1[i - 1];
    while(begin <= end) {
        //对数时间找到i，j 二分搜索思想
        i = (begin + end) / 2;
        j = k - i;
        if(i > 0 && j < arr2.size() && arr1[i - 1] > arr2[j]) {
            end = i - 1;
        }
        else if(j > 0 && i < arr1.size() && arr2[j - 1] > arr1[i]) {
            begin = i + 1;
        }
        else break;
    }
    int left = max(arr1[i - 1], arr2[j - 1]);
    int right = min(arr1[i], arr2[j]);
    //特殊1 ：arr1 很短且arr1元素都很大
    if(i == 0) { // i为0，中位数一定在arr2中
        left = arr2[j - 1];
    }
    // 特殊2 arr2 很短且arr2元素都很大
    else if(j == 0) {
        left = arr1[i - 1];
    }
    //特殊3 arr1 
    if(i == len1) {
        right = arr2[j];
    }
    //特殊4
    else if(j == len2) {
        right = arr1[i];
    }
    if((len1 + len2) % 2) {
        return left;
    }
    else {
        return ((left + right) * 1.0) / 2;
    }
}
void test_mid() {
    vector<int> arr1(10), arr2(10), arr3(9);
    for(int i = 0; i < 10; i++) {
        arr1[i] = rand() % 21;
        arr2[i] = rand() % 21 + 1;
        arr3[i % 8] = rand() % 21;
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    sort(arr3.begin(), arr3.end());
    cout << "数组1元素:";
    for(int a : arr1) cout << a << " "; cout << endl;
    cout << "数组2元素:";
    for(int a : arr2) cout << a << " "; cout << endl;
    cout << "两数组的中位数:" << midval(arr1, arr2) << endl;
    // arr2 = {1, 3};arr3 = {2};
    cout << "数组1元素:";
    for(int a : arr2) cout << a << " "; cout << endl;
    cout << "数组2元素:";
    for(int a : arr3) cout << a << " "; cout << endl;
    cout << "两数组的中位数:" << midval(arr2, arr3) << endl;
}

// T6. 分治算法求解硬币选择问题
int coin_select(int n) {
    if(n == 1 || n == 3 || n == 5) return 1;
    else if(n == 2 || n == 4) return 2;
    else {
        int n1 = coin_select(n - 1) + 1;// 假设选取1分硬币
        int n2 = coin_select(n - 3) + 1;// 假设选取3分硬币
        int n3 = coin_select(n - 5) + 1;// 假设选取5分硬币
        return min({n1, n2, n3});
    }
}
void test_coin_select() {
    int val = 6;//所求的总面值
    cout << "组成" << val << "最少需要" << coin_select(val) << "枚面值为1或3或5的硬币" << endl;
}

// T7. 斐波那契数列
int fabnacci(int n) {// 简单递归--分治算法
    if(n == 0) return 0;
    if(n == 1 || n == 2) return 1;
    return fabnacci(n - 1) + fabnacci(n - 2);
}
void test_fabnacci() {
    int n = 30;
    cout << "斐波那契数列第" << n << "项:" << fabnacci(n) << endl;
}

// T8. LCS 最长公共子序列--分治算法
int LCS(string str1, string str2) {
    if(str1.empty() || str2.empty()) return 0;
    int n1 = str1.size(), n2 = str2.size();
    if(str1.back() == str2.back()) {
        return LCS(string(str1.begin(), str1.end() - 1), string(str2.begin(), str2.end() - 1)) + 1;
    }
    else return max(LCS(string(str1.begin(), str1.end() - 1), string(str2.begin(), str2.end())), LCS(string(str1.begin(), str1.end()), string(str2.begin(), str2.end() - 1)));
    return 1;
}
void test_LCS() {
    string str1 = "helloworld";
    string str2 = "hlweord";
    cout << "字符串1:" << str1 << endl;
    cout << "字符串2:" << str2 << endl;
    cout << "最长公共子序列长度为:" << LCS(str1, str2) << endl;
}

int main() {
    test_binary_search();
    cout << "-------------------------------------------------------------\n";
    test_fast_sort();
    cout << "-------------------------------------------------------------\n";
    test_topk_quick_sort();
    cout << "-------------------------------------------------------------\n";
    test_merge_sort();
    cout << "-------------------------------------------------------------\n";
    test_mergelist_k();
    cout << "-------------------------------------------------------------\n";
    test_mid();
    cout << "-------------------------------------------------------------\n";
    test_coin_select() ;
    cout << "-------------------------------------------------------------\n";
    test_fabnacci();
    cout << "-------------------------------------------------------------\n";
    test_LCS();
    cout << "-------------------------------------------------------------\n";
    return 0;
}