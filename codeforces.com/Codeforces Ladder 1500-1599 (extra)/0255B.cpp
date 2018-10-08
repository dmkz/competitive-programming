/*
    Problem: 255B. Code Parsing
    
    Solution: set, implementation, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s;
    std::set<int> x, y;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == 'x') x.insert(i); else y.insert(i);
    }
    while (!y.empty() && !x.empty()) {
        auto it_y = y.begin();
        auto it_x = x.lower_bound(*it_y);
        if (it_x != x.end()) {
            int py = *it_y;
            int px = *it_x;
            y.erase(it_y);
            x.erase(it_x);
            y.insert(px);
            x.insert(py);
            continue;
        }
        it_x = x.begin();
        it_y = y.lower_bound(*it_x);
        if (it_y != y.end()) {
            y.erase(it_y);
            x.erase(it_x);
            continue;
        }
        break;
    }
    std::string answ;
    while (!x.empty() || !y.empty()) {
        if (x.empty()) {
            answ.push_back('y');
            y.erase(y.begin());
        } else if (y.empty()) {
            answ.push_back('x');
            x.erase(x.begin());
        } else if (*y.begin() < *x.begin()) {
            answ.push_back('y');
            y.erase(y.begin());
        } else if (*y.begin() > *x.begin()) {
            answ.push_back('x');
            x.erase(x.begin());
        } else {
            throw 1;
        }
    }
    std::cout << answ;
    return 0;
}