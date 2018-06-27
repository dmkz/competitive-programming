/*
    "Баллы": бинарный поиск в массиве, O(n log(n))
*/

#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<ll> a(n);
    for (auto& it : a) {
        std::cin >> it;
    }
    
    while (q--) {
        ll value; 
        std::cin >> value; 
        std::cout << (std::binary_search(a.begin(), a.end(), value) ? "YES " : "NO ");
    }
    return 0;
}