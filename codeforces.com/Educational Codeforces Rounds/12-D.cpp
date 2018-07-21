/*
    Problem: 665D. Simple Subset
    
    Solution: constructive algorithm, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    // Prepare primes with sieve:
    const int LIMIT = (int)2e6;
    std::vector<bool> is_prime(1 + LIMIT, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= LIMIT; ++i) {
        if (!is_prime[i])continue;
        for (int j = i * i; j <= LIMIT; j += i) {
            is_prime[j] = false;
        }
    }
    
    // Input array and count items:
    int n; std::cin >> n;
    
    std::vector<int> count(1+1000*1000, 0);
    
    std::vector<int> arr(n);
    
    for (auto& it : arr) {
        std::cin >> it;
        count[it]++;
    }
    // Sort array and remove repeats:
    std::sort(arr.begin(), arr.end());
    arr.erase(std::unique(arr.begin(), arr.end()), arr.end());
    n = (int)arr.size();
    
    // Find answer (answer contains not greater then 2 unique numbers, only number 1 may be duplicated):
    int max = 0;
    std::pair<int,int> answ = {-1, -1};
    for (int i = 0; i < n; ++i) {
        int c1 = arr[i] == 1 ? count[arr[i]] : 1;
        if (c1 > max) {
            max = c1;
            answ = std::make_pair(i, -1);
        }
        for (int j = i+1; j < n; ++j) {
            if (is_prime[arr[i] + arr[j]]) {
                int c2 = 1;
                if (c1+c2 > max) {
                    answ = std::make_pair(i, j);
                    max = c1 + c2;
                }
            }
        }
    }
    
    std::vector<int> output;
    
    if (arr[answ.first] == 1) {
        for (int i = 0; i < count[1]; ++i) {
            output.push_back(1);
        }
    } else {
        output.push_back(arr[answ.first]);
    }
    if (answ.second != -1) {
        output.push_back(arr[answ.second]);
    }
    
    std::cout << output.size() << '\n';
    for (auto& it : output) {
        std::cout << it << ' ';
    }
    
    return 0;
}