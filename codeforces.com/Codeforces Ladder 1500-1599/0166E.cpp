/*
    Problem: 166E. Tetrahedron
    Solution: dynamic programming
*/
#include <iostream>
#include <vector>

const int mod = (int)1e9+7;

inline int add(int a, int b) {
    return (a+=b) >= mod ? a - mod : a;
}

int main() {
    int n; std::cin >> n;
    std::vector<int> prev(4), curr(4);
    curr[3] = 1;
    while (n--) {
        prev.swap(curr);
        std::fill(curr.begin(), curr.end(),0);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                curr[j] = add(curr[j], prev[i]);
            }
        }
    }
    std::cout << curr[3];
    return 0;
}