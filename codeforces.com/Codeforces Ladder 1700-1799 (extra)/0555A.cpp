/*
    Problem: 555A. Case of Matryoshkas
    
    Solution: greedy, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m;
    while (std::cin >> n >> m) {
        int answ = 0, needToUnion = 0;
        for (int id = 0; id < m; ++id) {
            int s; std::cin >> s;
            std::vector<int> arr(s);
            for (int i = 0; i < s; ++i) {
                std::cin >> arr[i];
            }
            int p = 0;
            while (p < s && arr[p] == p+1) {
                ++p;
            }
            needToUnion += (p != 0) + (s - p);
            answ += (p != 0 && p != s) + std::max(0, (s - p - 1));
        }
        answ += needToUnion-1;
        std::cout << answ << std::endl;
    }
    return 0;
}