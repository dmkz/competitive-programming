/*
    Problem: 385C. Bear and Prime Numbers
    Solution: sieve, number theory, dynamic programming, binary search
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    const int XMAX = (int)1e7;
    std::vector<int> firstPrimeDiv(1+XMAX);
    for (int i = 2; i * i <= XMAX; ++i) {
        if (firstPrimeDiv[i] != 0) continue;
        firstPrimeDiv[i] = i;
        for (int j = i * i; j <= XMAX; j += i) {
            if (firstPrimeDiv[j] == 0) {
                firstPrimeDiv[j] = i;
            }
        }
    }
    for (int i = 2; i <= XMAX; ++i) {
        if (!firstPrimeDiv[i]) {
            firstPrimeDiv[i] = i;
        }
    }
    
    std::vector<int> arr;
    
    int nItems; std::cin >> nItems;
    while (nItems--) {
        int x; std::cin >> x;
        int last = 1;
        while (x > 1) {
            int div = firstPrimeDiv[x];
            if (last != div) {
                arr.push_back(div);
                last = div;
            }
            x /= div;
        }
    }
    std::sort(arr.begin(), arr.end());
    
    int nQueries; std::cin >> nQueries;
    while (nQueries--) {
        int l, r; std::cin >> l >> r;
        auto it_l = std::lower_bound(arr.begin(), arr.end(), l);
        auto it_r = std::upper_bound(arr.begin(), arr.end(), r);
        std::cout << int(it_r - it_l) << '\n';
    }
    
    return 0;
}