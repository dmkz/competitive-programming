/*
    Problem: 389B. Fox and Cross
    Solution: implementation, constructive, O(n^2)
*/
#include <bits/stdc++.h>
int main() {
    std::vector<std::string> arr;
    for (int n; std::cin >> n; ) {
        arr.resize(n);
        for (auto &it : arr) std::cin >> it;
        auto validate = [&](int i, int j) {
            if (i+2 >= n) return false;
            if (j - 1 < 0 || j + 1 >= n) return false;
            int ci = i+1, cj = j;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di * di + dj * dj <= 1 && arr[ci+di][cj+dj] != '#') {
                        return false;
                    }
                }
            }
            return true;
        };
        auto remove = [&](int i, int j) {
            int ci = i+1, cj = j;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di * di + dj * dj <= 1) {
                        arr[ci+di][cj+dj] = '.';
                    }
                }
            }
        };
        bool ok = true;
        for (int i = 0; ok && i < n; i++) {
            for (int j = 0; ok && j < n; j++) {
                if (arr[i][j] == '#') {
                    if (!validate(i,j)) {
                        ok = false;
                        break;
                    }
                    remove(i,j);
                }
            }
        }
        std::cout << (ok ? "YES\n" : "NO\n");
    }
}