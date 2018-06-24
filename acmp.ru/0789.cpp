#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

typedef unsigned long long Int;

int main() {
    std::vector<Int> numbers;
    for (Int pow2 = 1; pow2 <= 1e18; pow2 *= 2) {
        for (Int pow3 = 1; pow2 * pow3 <= 1e18; pow3 *= 3) {
            for (Int pow5 = 1; pow2 * pow3 * pow5 <= 1e18; pow5 *= 5) {
                numbers.push_back(pow2 * pow3 * pow5);
            }
        }
    }
    std::sort(numbers.begin(), numbers.end());
    
    int n; std::cin >> n;
    assert((int)numbers.size() > n);
    std::cout << numbers[n-1];
    return 0;
}