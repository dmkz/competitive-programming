/*
    Problem: 384A. Coder
    Solution: constructive, O(n^2)
*/
#include <bits/stdc++.h>
int main() {
    int n, cnt = 0; std::cin >> n;
    std::vector<std::string> arr(n, std::string(n, '.'));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i+j)%2 == 0) {
                cnt++;
                arr[i][j] = 'C';
            }
        }
    }
    std::cout << cnt << '\n';
    for (auto &it : arr) std::cout << it << '\n';
    return 0;
}