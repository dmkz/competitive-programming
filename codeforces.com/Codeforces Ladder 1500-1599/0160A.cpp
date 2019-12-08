/*
    Problem: 160A. Twins
    Solution: greedy, sorting
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto& it : a) {
        std::cin >> it;
    }
    std::sort(a.begin(), a.end(), std::greater<int>());
    int sum = 0, part1 = 0; for (auto& it : a) sum += it;
    int i;
    for (i = 0; i < n; ++i) {
        part1 += a[i];
        if (2*part1 > sum) {
            break;
        }
    }
    std::cout << i+1;
    return 0;
}