/*
    Problem: 289B. Polo the Penguin and Matrix
    Solution: sorting, brute force, implementation
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int nRows, nCols, diff;
    std::cin >> nRows >> nCols >> diff;
    
    std::vector<int> arr(nRows*nCols);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    const int INF = (int)1e9+1;
    int answ = INF;
    for (int s = arr.front(); s <= arr.back(); s += diff) {
        int cnt = 0;
        for (auto& it : arr) {
            int temp = std::abs(it-s);
            if (temp % diff != 0) {
                cnt = INF;
                break;
            }
            cnt += temp / diff;
        }
        answ = std::min(cnt, answ);
    }
    if (answ == INF) answ = -1;
    std::cout << answ;
    return 0;
}