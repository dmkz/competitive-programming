/*
    Problem: 7265. The secret code
    
    Solution: probability theory, bfs, O(n * m + n * k * log(k))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

typedef long double ld;

struct Pair {
    
    int pos;
    
    ld value;
    
    Pair(int pos_ = 0, ld value_ = 0) : pos(pos_), value(value_) { }
};

typedef std::vector<ld> vd;
typedef std::vector<vd> vvd;
typedef std::vector<Pair> vp;
typedef std::vector<vp> vvp;

ld prod(const vp &a) {
    ld res = 1;
    for (auto &it : a) { res *= it.value; }
    return res;
}

bool operator<(const vp& a, const vp& b) {
    ld prod1 = prod(a), prod2 = prod(b);
    if (prod1 > prod2) {
        return true;
    }
    if (prod1 < prod2) {
        return false;
    }
    assert(a.size() == b.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i].pos < b[i].pos) {
            return true;
        }
        if (a[i].pos > b[i].pos) {
            return false;
        }
    }
    return false;
}

ld solve(const int nRings, const int nVar, const int nTry, vvd arr) {
    for (auto & it : arr) { std::sort(it.begin(), it.end(), std::greater<ld>()); }
    vvp answ;
    std::set<vp> queue;
    vp initial;
    for (int i = 0; i < nRings; ++i) {
        initial.push_back(Pair(0, arr[i][0]));
    }
    queue.insert(initial);
    while (!queue.empty() && (int)answ.size() < nTry) {
        auto curr = *queue.begin();
        queue.erase(queue.begin());
        answ.push_back(curr);
        for (int i = 0; i < nRings; ++i) {
            if (curr[i].pos+1 < nVar) {
                int pos = ++curr[i].pos;
                curr[i].value = arr[i][pos];
                queue.insert(curr);
                if ((int)queue.size() > nTry) {
                    queue.erase(std::prev(queue.end()));
                }
                pos = --curr[i].pos;
                curr[i].value = arr[i][pos];
            }
        }
    }
    ld res = 0;
    for (auto & curr : answ) {
        res += prod(curr);
    }
    return res;
}

int main() {
    int n, m, k;
    while (scanf("%d", &n) == 1) {
        assert(scanf("%d", &m) == 1);
        assert(scanf("%d", &k) == 1);
        vvd arr(n, vd(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int value;
                assert(scanf("%d", &value) == 1);
                arr[i][j] = (ld)value / 100;
            }
            std::sort(arr[i].begin(), arr[i].end(), std::greater<ld>());
        }
        printf("%0.9f\n", double(solve(n,m,k,arr)));
    }
    return 0;
}