#include <iostream>
using namespace std;
int binary_1(int arr[],int n,int k){//二分搜索--循环
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
    return INT_MIN;
}
//回顾递归
int recursion(int n){//递归阶乘
    if(n == 0){throw;}
    else if(n == 1){
        return 1;
    }
    return n * recursion(n-1);
} 
int binary_2(int arr[],int left,int right,int k){//二分搜索--递归
    int mid = (left + right)/2;
    if(left > right)throw;//递归结束条件
    if(arr[mid] == k)return mid;
    else if(arr[mid] > k){
        right = mid - 1;
        return binary_2(arr,left,right,k);
    }
    else if(arr[mid] < k){
        left = mid + 1;
        return binary_2(arr,left,right,k);
    }
}

int main(){
    int arr[9] = {1,2,3,4,5,6,7,8,9};
    cout<<binary_1(arr,9,9)<<endl;
    cout<<binary_2(arr,0,8,9)<<endl;
    cout<<recursion(10)<<endl;
    system("pause");
    
}