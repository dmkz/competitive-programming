/*
    Problem: 631D. Messenger
    
    Solution: strings, prefix function, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;
typedef std::vector<int> vi;

struct Pair {
    ll len; char c;
    
    Pair(ll len_ = 0, char c_ = 0) : len(len_), c(c_) { }
};

typedef std::vector<Pair> vp;

bool operator==(const Pair &lhs, const Pair &rhs) {
    return lhs.len == rhs.len && lhs.c == rhs.c;
}

vp input(int nBlocks) {
    vp t;
    for (int i = 0; i < nBlocks; ++i) {
        int l; char c;
        scanf("%d-%c", &l, &c);
        if (t.empty()) {
            t.push_back(Pair(0,c));
        }
        if (t.back().c == c) {
            t.back().len += l;
        } else {
            t.push_back(Pair(l,c));
        }
    }
    return t;
}

vi prefix_function(vp t, vp s) {
    t.insert(t.begin(), s.begin(), s.end());
    t.insert(t.begin()+s.size(), Pair(0, '#'));
    int len = 0;
    vi pref(1+(int)t.size(),0);
    for (int i = 1; i < (int)t.size(); ++i) {
        while (len > 0 && !(t[len] == t[i])) {
            len = pref[len];
        }
        len += (t[len] == t[i]);
        pref[i+1] = len;
    }
    pref.erase(pref.begin(), pref.begin()+s.size()+2u);
    return pref;
}

int main() {    
    int n, m;
    while (2 == scanf("%d %d", &n, &m)) {
        vp t = input(n), s = input(m);
        n = (int)t.size(), m = (int)s.size();
        if (m > n) {
            std::cout << 0 << std::endl;
            continue;
        }
        vi prefFunc;
        if (m > 2) {
            prefFunc = prefix_function(t, vp(std::next(s.begin()), std::prev(s.end())));
        }
        
        ll answ = 0;
        for (int i = 0; i + m - 1 < n; ++i) {
            if (t[i].c != s[0].c || s[0].len > t[i].len) {
                continue;
            }
            if (s.size() == 1u) {
                answ += t[i].len - s[0].len + 1;
                continue;
            }
            // all blocks till last block must be equal
            bool eq = true;
            if (m > 2) {
                eq = eq && prefFunc[i+m-2] == m-2;
            }
            eq = eq && s[m-1].len <= t[i+m-1].len && s[m-1].c == t[i+m-1].c;
            // t[i+1] ... t[i + m - 2]
            answ += eq;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}