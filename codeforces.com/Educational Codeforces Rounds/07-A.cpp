/*
    Problem: 622A. Infinite Sequence
    
    Solution: math, implementation, O(sqrt(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cassert>

typedef long long ll;

int main() {
    ll pos; std::cin >> pos;
    if (pos == 1) {
        std::cout << 1 << std::endl;
        return 0;
    }
    ll last = 1;
    while (pos > (last+1) * (last + 2) / 2) {
        ++last;
    }
    // pos > last * (last+1) / 2
    assert(pos >= last * (last+1)/2);
    pos -= last * (last+1) / 2;
    std::cout << pos << std::endl;
    return 0;
}