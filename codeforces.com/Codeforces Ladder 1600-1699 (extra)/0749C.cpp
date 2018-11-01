/*
    Problem: 749C. Voting
    
    Solution: greedy, set, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

struct Pair {
    int pos; char type;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.pos < b.pos || (a.pos == b.pos && a.type < b.type);
}

char solve(const int n, std::string s) {
    std::set<Pair> sequence, posD, posR;
    for (int i = 0; i < n; ++i) {
        sequence.insert(Pair{i, s[i]});
        if (s[i] == 'D') {
            posD.insert(Pair{i, s[i]});
        } else {
            posR.insert(Pair{i, s[i]});
        }
    }
    while (!(posR.empty() || posD.empty())) {
        for (auto it = sequence.begin(); !(posR.empty() || posD.empty()) && it != sequence.end(); it++) {
            if (it->type == 'D') {
                auto toErase = posR.lower_bound(Pair{it->pos, 'R'});
                if (toErase == posR.end()) { toErase = posR.begin(); }
                sequence.erase(*toErase);
                posR.erase(*toErase);
            } else {
                auto toErase = posD.lower_bound(Pair{it->pos, 'D'});
                if (toErase == posD.end()) { toErase = posD.begin(); }
                sequence.erase(*toErase);
                posD.erase(*toErase);
            }
        }
    }
    return posR.empty() ? 'D' : 'R';
}

int main() {
    int n; std::string s;
    while (std::cin >> n >> s) {
        std::cout << solve(n, s) << std::endl;
    }
    return 0;
}