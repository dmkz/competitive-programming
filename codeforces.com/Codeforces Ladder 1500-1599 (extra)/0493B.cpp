/*
    Problem: 493B. Vasya and Wrestling
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <numeric>
#define all(x) (x).begin(), (x).end()
typedef long long ll;
int main() {
    int n; std::cin >> n;
    std::vector<int> x, y;
    std::string last;
    while (n--) {
        int a; std::cin >> a;
        if (a > 0) { last = "first"; x.push_back(a); }
        if (a < 0) { last = "second" ;y.push_back(-a); }
        
    }
    ll s1 = std::accumulate(all(x), ll(0));
    ll s2 = std::accumulate(all(y), ll(0));
    if (s1 > s2) { std::cout << "first"; return 0; }
    if (s1 < s2) { std::cout << "second"; return 0; }
    if (x > y) { std::cout << "first"; return 0; }
    if (x < y) { std::cout << "second"; return 0; }
    std::cout << last;
    return 0;
}