/*
    Problem: 136A. Presents
    Solution: implementation
*/
#include <iostream>
#include <vector>
int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(1+n);
    for (int i = 1; i <= n; ++i) {
        int p; std::cin >> p;
        arr[p] = i;
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << arr[i] << ' ';
    }
    return 0;
}