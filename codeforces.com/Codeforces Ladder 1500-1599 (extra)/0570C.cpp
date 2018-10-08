/*
    Problem: 570C. Replacement
    
    Solution: implementation, std::set, O((n+m)*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <set>
#include <cassert>

struct Pair {
    int pos, len; char symbol;
};

bool operator<(const Pair& a, const Pair& b) {
    if (a.pos < b.pos) return true;
    if (a.pos > b.pos) return false;
    return a.len < b.len || (a.len == b.len && a.symbol < b.symbol);
}

bool operator>(const Pair& a, const Pair& b) {
    return b < a;
}

bool operator==(const Pair& a, const Pair& b) {
    return !(a < b || b < a);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, m; std::cin >> n >> m;
    std::string s; std::cin >> s;
    s = '?' + s + '?'; n += 2;
    std::set<Pair> set;
    int nOp = 0, begin = n;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '.') {
            begin = std::min(begin, i);
            continue;
        }
        if (begin < i) {
            nOp += std::max(0, (i-begin)-1);
            set.insert(Pair{begin, i-begin, '.'});
            begin = n;
        }
        set.insert(Pair{i, 1, s[i]});
    }
    
    for (int i = 0; i < m; ++i) {
        int p; char c; std::cin >> p >> c;
        Pair pair{p, 1, c};
        auto it = set.lower_bound(pair);
        assert(it != set.end());
        if (it->pos > p) {
            it = std::prev(it);
        }
        assert(it->pos <= p && p <= it->pos+it->len-1);
        if (c == '.') {
            if (it->symbol == '.') {
                std::cout << nOp << "\n";
                continue;
            }
            auto prev = std::prev(it);
            auto next = std::next(it);
            assert(it->len == 1 && it->pos == p);
            Pair temp{p, 1, '.'};
            if (prev->symbol == '.') {
                temp.pos = prev->pos;
                temp.len += prev->len;
                nOp++;
                set.erase(prev);
            }
            if (next->symbol == '.') {
                temp.len += next->len;
                nOp++;
                set.erase(next);
            }
            set.insert(temp);
            set.erase(it);
        } else {
            if (it->len > 1) {
                assert(it->len >= 2 && it->symbol == '.');
                Pair left = *it;
                left.len = p-left.pos;
                if (left.len > 0) {
                    nOp--;
                    set.insert(left);
                }
                Pair right = *it;
                right.len = right.pos+right.len-(p+1);
                right.pos = p+1;
                if (right.len > 0) {
                    nOp--;
                    set.insert(right);
                }
            }
            set.erase(it);
            set.insert(Pair{p,1,c});
        }
        std::cout << nOp << "\n";
    }
    return 0;
}