#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-result"

typedef int64_t Int;

Int solve(int pos, std::vector<Int> a) {
    assert(pos < (int)a.size());
    Int v = a[pos];
    a[pos] = 0;
    Int inc = v / 14;
    for (auto& it : a) it += inc;
    v -= inc * 14;
    while (v > 0) {
        pos = (pos + 1) % 14;
        a[pos]++;
        v--;
    }
    Int sum = 0;
    for (auto it : a) {
        if (it % 2 == 0) {
            sum += it;
        }
    }
    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    std::vector<Int> a(14); 
    for (auto& it : a) {
        std::cin >> it;
    }
    
    Int answ = 0;
    for (int pos = 0; pos < 14; ++pos) {
        answ = std::max(answ, solve(pos, a));
    }
    
    std::cout << answ << std::endl;
    return 0;
}