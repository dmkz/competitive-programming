/*
    Problem: 253B. Physics Practical
    Solution: dynamic programming
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt" stdout);
    int n; std::cin >> n;
    std::vector<int> count(1+5000,0);
    for (int i = 0; i < n; ++i) {
        int val; std::cin >> val;
        count[val]++;
    }
    std::vector<int> sum(1+5000,0);
    for (int i = 1; i <= 5000; ++i) sum[i] = sum[i-1] + count[i];
    
    int answ = n;
    for (int i = 1; i <= 5000; ++i) {
        answ = std::min(answ, n - sum[std::min(5000,2*i)]+sum[i-1]);
    }
    std::cout << answ;
    return 0;
}