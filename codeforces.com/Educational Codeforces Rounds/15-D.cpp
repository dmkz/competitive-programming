/*
    Problem: 702D. Road to Post Office
    
    Solution: math, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    ll d, k, a, b, t; 
    std::cin >> d >> k >> a >> b >> t;
    
    if (d <= k) { std::cout << a * d; return 0; }
    
    if (k*(b-a)-t <= 0) {
        std::cout << a * k + b * (d-k);
        return 0;
    }
    
    ll nCrash = d / k;
    
    ll answ = std::min(nCrash * t + d * a, (nCrash-1) * t + nCrash * k * a + d % k * b);
    
    std::cout << answ;
    
    return 0;
}