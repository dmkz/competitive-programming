/*
    Problem: 797E. Array Queries
    
    Solution: sqrt-decomposition, dynamic programming, O(n*sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
const int MXN = (int)1e5, MXK = 256;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    static int arr[MXN];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int nQ; std::cin >> nQ;
    static int answer[1+MXK][MXN];
    for (int k = 1; k <= MXK; ++k) {
        for (int p = n-1; p >= 0; --p) {
            answer[k][p] = (p + arr[p] + k < n) ? (answer[k][p + arr[p] + k] + 1) : 1;
        }
    }
    while (nQ--) {
        int p, k; std::cin >> p >> k; --p;
        int cnt = 0;
        if (k <= MXK) {
            cnt = answer[k][p];
        } else {
            cnt = 0;
            while (p < n) {
                p += arr[p] + k; 
                ++cnt; 
            }
        }
        std::cout << cnt << '\n';
    }
    return 0;
}