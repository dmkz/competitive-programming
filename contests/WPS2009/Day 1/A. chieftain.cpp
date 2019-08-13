/*
    Problem: A. Chieftain
    Solution: linear max, O(n)
*/
#include <bits/stdc++.h>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int max = INT_MIN, cnt = 0, n;
    std::cin >> n;
    while (n--) {
        int v; std::cin >> v;
        if (v > max) { max = v; cnt = 0; }
        cnt += (v == max);
    }
    std::cout << cnt << std::endl;
    return 0;
}