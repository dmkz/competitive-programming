/*
    Problem: 598A. Tricky Sum
    
    Solution: math, arithmetic progression, O(q * log(v))
*/

#include <iostream>

typedef long long ll;

ll sum2(int v) {
    ll s = 0, p = 1;
    while (p <= v) {
        s += p; p *= 2;
    }
    return s;
}

inline ll answer(int v) {
    return (ll)v * (v+1) / 2 - 2 * sum2(v);
}

int main() {    
    int nQ; std::cin >> nQ;
    while (nQ--) {
        int v;
        std::cin >> v;
        std::cout << answer(v) << "\n";
    }
    return 0;
}