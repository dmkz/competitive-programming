/*
    Problem: 359D. Pair of Numbers
    
    Solution: minimum queue, binary search, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cassert>

int gcd(int a, int b) {
    while (b != 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

struct Node {
    int value, min, gcd;
};

struct MinGCDQueue {
    
    std::vector<Node> s_in, s_out;
    
    void push(int value) {
        int g = s_in.empty() ? value :    ::gcd(value, s_in.back().gcd);
        int m = s_in.empty() ? value : std::min(value, s_in.back().min);
        s_in.push_back(Node{value, m, g});
    }
    
    void pop() {
        if (s_out.empty()) {
            while (!s_in.empty()) {
                int val = s_in.back().value;
                s_in.pop_back();
                int min = s_out.empty() ? val : std::min(val, s_out.back().min);
                int gcd = s_out.empty() ? val :    ::gcd(val, s_out.back().gcd);
                s_out.push_back(Node{val, min, gcd});
            }
        }
        assert(!s_out.empty());
        s_out.pop_back();
    }
    
    void get(int& min, int& gcd) {
        if (s_in.empty()) {
            assert(!s_out.empty());
            min = s_out.back().min;
            gcd = s_out.back().gcd;
        } else if (s_out.empty()) {
            assert(!s_in.empty());
            min = s_in.back().min;
            gcd = s_in.back().gcd;
        } else {
            min = std::min(s_in.back().min, s_out.back().min);
            gcd =    ::gcd(s_in.back().gcd, s_out.back().gcd);
        }
    }
    
};

std::vector<int> solve(const std::vector<int>& arr, const int len) {
    // Init queue:
    MinGCDQueue queue;
    for (int i = 0; i < len; ++i) {
        queue.push(arr[i]);
    }
    // Check first segment:
    int min, gcd;
    queue.get(min, gcd);
    std::vector<int> answ;
    if (min == gcd) {
        answ.push_back(1);
    }
    // Check other segments:
    for (int i = 1; i + len - 1 < (int)arr.size(); ++i) {
        queue.pop();
        queue.push(arr[i+len-1]);
        queue.get(min, gcd);
        if (min == gcd) {
            answ.push_back(i+1);
        }
    }
    return answ;
}

int main() {
    // Input:
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) scanf("%d", &it);
    int low = 0, high = n+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (solve(arr, mid).empty()) {
            high = mid; 
        } else low = mid;
    }
    assert(low >= 1);
    auto answ = solve(arr, low);
    printf("%d %d\n", (int)answ.size(), low-1);
    for (auto& it : answ) printf("%d ", it);
    return 0;
}