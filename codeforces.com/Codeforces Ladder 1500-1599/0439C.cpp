/*
    Problem: 439C. Devu and Partitioning of the Array
    Solution: brute force, constructive, implementation, number theory
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nItems, nGroups, nEvenGroups;
    std::cin >> nItems >> nGroups >> nEvenGroups;
    int nOddGroups = nGroups - nEvenGroups;
    std::vector<int> odd, even;
    for (int i = 0; i < nItems; ++i) {
        int item; std::cin >> item;
        if (item % 2 == 0) even.push_back(item); else odd.push_back(item);
    }
    
    std::vector<std::vector<int>> groups(nGroups);
    for (int i = 0; i < nOddGroups; ++i) {
        if (odd.empty()) { std::cout << "NO"; return 0; }
        groups[i].push_back(odd.back()); odd.pop_back();
        --nItems;
    }
    
    for (int i = nOddGroups; i < nGroups; ++i) {
        if (!even.empty()) {
            groups[i].push_back(even.back());
            even.pop_back();
            --nItems;
        } else if (odd.size() >= 2u) {
            groups[i].push_back(odd.back()); odd.pop_back();
            groups[i].push_back(odd.back()); odd.pop_back();
            nItems -= 2;
        } else { std::cout << "NO"; return 0; }
    }
    
    for (int g = 0; nItems; g = (++g) >= nGroups ? g - nGroups : g) {
        if (!even.empty()) {
            groups[g].push_back(even.back());
            even.pop_back();
            --nItems;
        } else if (odd.size() >= 2u) {
            groups[g].push_back(odd.back()); odd.pop_back();
            groups[g].push_back(odd.back()); odd.pop_back();
            nItems -= 2;
        } else { std::cout << "NO"; return 0; }
    }
    
    std::cout << "YES\n";
    for (auto& g : groups) {
        std::cout << g.size();
        for (auto& it : g) {
            std::cout << ' ' << it;
        }
        std::cout << '\n';
    }
    return 0;
}