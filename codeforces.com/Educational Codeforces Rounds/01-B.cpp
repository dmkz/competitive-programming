/*
    Problem: 598B. Queries on a String
    
    Solution: algorithm, rotate, strings, O(m * len)
*/

#include <iostream>
#include <algorithm>
#include <string>

int main() {
    int nQ; std::string s; 
    std::cin >> s >> nQ;
    while (nQ--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        --l, --r;
        k %= (r-l+1);
        std::rotate(s.begin()+l, s.begin()+r+1-k, s.begin()+r+1);
    }
    std::cout << s;
    return 0;    
}