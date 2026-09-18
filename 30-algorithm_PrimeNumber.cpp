#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
using namespace std;

// 找质数算法————试除法，埃式筛，欧拉筛
ostream& operator<<(ostream& c, const vector<int>&nums) {  
    for(int i : nums) {
        c << i << ' ';
    }
    c << endl;
    return c;
}
vector<int> Trial(vector<int>& nums) { // 试除法，时间复杂度O(n * √n), 简单但低效
    int n = nums.size();
    vector<int> ans;
    for(int num : nums) {
        if(num <= 2) continue;
        bool flag = true;
        for(int i = 2; i * i <= num; i++) {
            if(num % i == 0) {
                flag = false;
                break;
            }
        }
        if(flag) ans.push_back(num);
    }
    return ans;
}

vector<bool> Eratosthenes_Sieve(int n) { // 埃式筛
    if(n < 2) return {};
    vector<bool> is_prime(n + 1, true); // 初始假设全是素数
    for(int i = 2; i * i <= n; i++) {
        if(is_prime[i]) {
            for(int j = i * i; j <= n; j += i) { // 每次将不是素数i的倍数标记为非素数，从 j=i*i 开始标记
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}
vector<int> Eratosthenes_Sieve_nums(vector<int>& nums) {
    int mx = ranges::max(nums);
    vector<bool> is_prime = Eratosthenes_Sieve(mx);
    if(is_prime.empty()) {
        return {};
    }
    vector<int> prime;
    for(int num : nums) {
        if(is_prime[num]) {
            prime.push_back(num);
        }
    }
    return prime;
}

vector<bool> Eurel_sieve(int n) { // 欧拉筛（线性筛）
    // 对遍历到的每一个数字，乘以素数表中的数字
    vector<int> prime;
    vector<bool> is_prime(n + 1, true);
    for(int i = 2; i <= n; i++) {
        if(is_prime[i]) {
            prime.push_back(i);
        }
        for(int j = 0; j < prime.size() && i * prime[j] <= n; j++) {
            is_prime[prime[j] * i] = false;
            if(i % prime[j] == 0) { // 确保每个和数都只被最小质因数遍历到
                break;
            }
        }
    }
    return is_prime;
}
vector<int> Eurel_sieve_nums(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans;
    vector<bool> is_prime = Eurel_sieve(ranges::max(nums));;
    for(int i = 0; i < n; i++) {
        if(nums[i] > 1 && is_prime[nums[i]]) {
            ans.push_back(nums[i]);
        }
    }
    return ans;
}

int main() {
    vector<int> nums{12, 45, 78, 3, 99, 34, 67, 21, 56, 88, 9, 41, 73, 26, 94, 17, 62, 38, 85, 50};
    cout << "试除法: " << Trial(nums);
    cout << "埃式筛: " << Eratosthenes_Sieve_nums(nums);
    cout << "欧拉筛: " << Eurel_sieve_nums(nums);
}