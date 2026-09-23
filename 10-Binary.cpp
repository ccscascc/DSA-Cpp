#include <iostream>
#include <vector>
using namespace std;
int binary_1(vector<int>& arr, int k){//二分搜索--循环
    int n = arr.size();
    int left = 0,right = n-1;
    int mid = (left + right)/2;
    while(left <= right){
        if(k<arr[mid]){
            right = mid - 1;
        }
        else if(k>arr[mid]){
            left = mid + 1;
        }
        if(k == arr[mid]){
            return mid;
        }
        mid = (left + right)/2;
    }
    return -1; // 只在找到时返回有效坐标，当找不到时返回-1
    // 适用范围有限，在有多个元素等于目标值时，不一定返回哪个
}
//回顾递归
int recursion(int n){//递归阶乘
    if(n == 0) return -1;
    else if(n == 1){
        return 1;
    }
    return n * recursion(n-1);
} 
int binary_2(vector<int>& arr, int left, int right, int k){//二分搜索--递归
    if(left > right) return -1;
    int mid = (left + right) / 2;
    if(arr[mid] == k) return mid;
    else if(arr[mid] > k) return binary_2(arr, left, mid - 1, k);
    else return binary_2(arr, mid + 1, right, k);
    return -1;
}

int lower_binary(vector<int>& nums, int target) { // 二分搜索优化
    int n = nums.size();
    int left = 0, right = n - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2; // 防止溢出，相当于 (left + right) / 2;
        if(nums[mid] < target) left = mid + 1;
        else right = mid - 1; // right最多左移到最后一个比target小的位置
    }
    return left; // 返回第一个大于等于target的元素的下标
    // 即使数组中没有找到目标值，也会返回比这个数大的第一个数
}

int main(){
    vector<int> arr{1,2,3,4,5,5,5,5,6,7,8,9};
    cout << binary_1(arr, 5) << endl;
    cout << binary_2(arr, 0, arr.size(), 5) << endl;
    cout << lower_binary(arr, 5) << endl;
}
