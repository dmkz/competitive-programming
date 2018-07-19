/*
    Problem: 609B. The Best Gift
    
    Solution: math, implementation, O(n + m^2)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

typedef int64_t Int;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    Int nBooks, nGenres; std::cin >> nBooks >> nGenres;
    
    std::vector<Int> booksInGenres(nGenres);
    for (Int i = 0; i < nBooks; ++i) {
        Int genre; std::cin >> genre; --genre;
        booksInGenres[genre]++;
    }
    
    Int answer = 0;
    for (Int i = 0; i < nGenres; ++i) {
        for (Int j = i+1; j < nGenres; ++j) {
            answer += booksInGenres[i] * booksInGenres[j];
        }
    }
    std::cout << answer;
    
    return 0;
}