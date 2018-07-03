/*
    Solution: Greatest frequency element, O(n log(n))
*/

#include <iostream>
#include <vector>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::map<int,int> count;
    
    int n; std::cin >> n;
    while (n--) {
        int coin; std::cin >> coin;
        count[coin]++;
    }
    
    int answ = 0;
    for (auto& p: count) {
        answ = std::max(answ, p.second);
    }
    std::cout << answ;
    return 0;
}