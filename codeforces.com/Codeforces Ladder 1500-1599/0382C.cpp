/*
    Problem: 382C. Arithmetic Progression
    Solution: implementation, sorting, constructive
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    if (n == 1) { std::cout << -1; return 0; }
    if (n == 2) {
        if (arr[0] == arr[1]) {
            std::cout << 1 << '\n' << arr[0];
            return 0;
        }
        int diff = arr[1] - arr[0];
        if (diff % 2 == 0) {
            std::cout << 3 << '\n' << arr[0] - diff << ' ' << arr[0] + diff / 2 << ' ' << arr[1] + diff;
        } else {
            std::cout << 2 << '\n' << arr[0] - diff << ' ' << arr[1] + diff;
        }
        return 0;
    }
    int diff = std::min(arr[1]-arr[0], arr[2]-arr[1]);
    std::vector<int> cand;
    for (int i = 1; i < n; ++i) {
        if (arr[i] - arr[i-1] == 2 * diff) {
            cand.push_back(arr[i] - diff);
        } else if (arr[i] - arr[i-1] != diff) {
            std::cout << 0; return 0;
        }
    }
    std::sort(cand.begin(), cand.end());
    cand.erase(std::unique(cand.begin(), cand.end()), cand.end());
    if (cand.size() == 1u) {
        std::cout << 1 << '\n' << cand.front();
        return 0;
    } else if (cand.size() >= 2u) {
        std::cout << 0;
        return 0;
    }
    int a = arr.front()-diff, b = arr.back()+diff;
    if (a == b) {
        std::cout << 1 << '\n' << a;
    } else {
        std::cout << 2 << '\n' << a << ' ' << b;
    }
    return 0;
}