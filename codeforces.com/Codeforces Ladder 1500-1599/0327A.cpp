/*
    Problem: 327A. Flipping Game
    Solution: brute force, dynamic programming
*/
#include <iostream>
#include <vector>
int main() {
    int n; std::cin >> n;
    std::vector<int> arr(1+n), pref(1+n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> arr[i];
        pref[i] = pref[i-1]+arr[i];
    }
    int answ = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int temp = pref[n] - 2*(pref[j] - pref[i-1]) + (j-i+1);
            answ = std::max(answ, temp);
        }
    }
    std::cout << answ;
    return 0;
}