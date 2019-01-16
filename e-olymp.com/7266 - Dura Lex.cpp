/*
    Problem: 7266. Dura Lex
    
    Solution: probability theory, expected value, gready, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

struct Triple {
    int p, d, i;
};

bool operator<(const Triple &lhs, const Triple &rhs) {
    int diff = -lhs.p * rhs.d + rhs.p * lhs.d;
    return diff < 0 || (diff == 0 && lhs.i < rhs.i);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<Triple> tr; std::vector<int> extra, answer;
        for (int i = 1, p, d; i <= n; ++i) {
            std::cin >> d >> p;
            if (p == 0 && d == 0) {
                extra.push_back(i);
            } else {
                tr.push_back(Triple{p, d, i});
            }
        }
        std::sort(extra.begin(), extra.end(), std::greater<int>());
        std::sort(tr.begin(), tr.end());
        for (auto &t : tr) {
            while (!extra.empty() && extra.back() < t.i) {
                answer.push_back(extra.back());
                extra.pop_back();
            }
            answer.push_back(t.i); 
        }
        while (!extra.empty()) {
            answer.push_back(extra.back());
            extra.pop_back();
        }
        for (auto &id : answer) { std::cout << id << ' '; }
        std::cout << std::endl;
    }
    return 0;
}