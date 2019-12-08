/*
    Problem: 493C. Vasya and Basketball
    Solution: binary search, brute force, sorting
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int sa; std::cin >> sa;
    std::vector<int> a(sa);
    for (auto& it : a) std::cin >> it;
    std::sort(a.begin(), a.end());
    
    int sb; std::cin >> sb;
    std::vector<int> b(sb);
    for (auto& it : b) std::cin >> it;
    std::sort(b.begin(), b.end());
    
    std::vector<int> c;
    std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(c));
    
    int best_na = 0, best_nb = (int)1e9;
    for (auto& item : c) {
        for (int d = std::max(item-1,0); d <= item+1; ++d) {
            int na = int(std::upper_bound(a.begin(), a.end(), d) - a.begin());
            na = na * 2 + (sa - na) * 3;
            
            int nb = int(std::upper_bound(b.begin(), b.end(), d) - b.begin());
            nb = nb * 2 + (sb - nb) * 3;
            
            if (na-nb > best_na-best_nb || (na-nb == best_na-best_nb && na > best_na)) {
                best_na = na;
                best_nb = nb;
            }
        }
    }
    std::cout << best_na << ':' << best_nb;
    return 0;
}