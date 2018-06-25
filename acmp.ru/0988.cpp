#include <iostream>
#include <cassert>

typedef unsigned long long ull;

std::string solve(ull k, ull p) {
    ull len = 1, lvl = 1;
    while (lvl < k && len < p) {
        len = 2 * len + 1;
        ++lvl;
    }
    if (lvl == k && p > len) {
        return "No solution";
    }
    while (lvl > 0) {
        len = len / 2;
        if (p == len+1) {
            break;
        } else if (p > len+1) {
            p -= len+1;
        }
        lvl--;
    }
    assert(lvl > 0);
    return std::to_string(lvl);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nTests; std::cin >> nTests;
    while (nTests--) {
        ull k, p; 
        std::cin >> k >> p;
        std::cout << solve(p, k) << '\n';
    }
    return 0;
}