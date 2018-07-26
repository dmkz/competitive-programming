/*
    Problem: 0522D. Closest Equals

    Solution: Mo's algorithm, Sqrt-Decomposition, O(n sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

struct Statistic {
    
    std::vector<int> count, group;
    
    static const int gsize = 707;
    
    Statistic(const int mxValue) 
        : count(mxValue+1, 0)
        , group((mxValue + gsize) / gsize, 0)
    { }
    
    inline void insert(int value) {
        count[value]++;
        group[value / gsize]++;
    }
    
    inline void remove(int value) {
        count[value]--;
        group[value / gsize]--;
    }
    
    int solve() const {
        int g = 0;
        while (g < (int)group.size() && group[g] == 0) {
            ++g;
        }
        if (g >= (int)group.size()) {
            return -1;
        }
        const int begin = g * gsize;
        const int after = std::min(begin + gsize, (int)count.size());
        for (int i = begin; i < after; ++i) {
            if (count[i] > 0) {
                return i;
            }
        }
        throw 1;
    }
};

struct Query {
    int l, r, id;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, nQueries;
    std::cin >> n >> nQueries;
    
    std::vector<int> arr(n), coord;
    for (auto& it : arr) { 
        std::cin >> it; 
        coord.push_back(it); 
    }
    
    std::sort(coord.begin(), coord.end());
    coord.erase(std::unique(coord.begin(), coord.end()), coord.end());
    
    for (auto& it : arr) {
        it = int(std::lower_bound(coord.begin(), coord.end(), it) - coord.begin());
    }
    
    std::vector<int> next(n, n), prev(n, n), pos(n, -1);
    
    for (int i = 0; i < n; ++i) {
        const int p = pos[arr[i]];
        if (p != -1) {
            prev[i] = next[p] = i - p;
        }
        pos[arr[i]] = i;
    }
    
    std::vector<Query> queries;
    for (int i = 0; i < nQueries; ++i) {
        int l, r;
        std::cin >> l >> r;
        queries.push_back(Query{l-1, r-1, i});
    }
    
    const int gsize = 707;
    
    std::sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        if (a.l / gsize == b.l / gsize) {
            return (((a.l / gsize) & 1) ? a.r < b.r : a.r > b.r);
        } else {
            return (a.l / gsize < b.l / gsize);
        }
    });
    
    int l = 0, r = -1;
    Statistic stat(n-1);
    
    std::vector<int> answer(nQueries);
    
    for (auto& q : queries) {
        while (r+1 <= q.r) {
            ++r;
            if (r-prev[r] >= l) {
                stat.insert(prev[r]);
            }
        }
        while (l+1 <= q.l) {
            if (l+next[l] <= r) {
                stat.remove(next[l]);
            }
            ++l;
        }
        while (l-1 >= q.l) {
            --l;
            if (l+next[l] <= r) {
                stat.insert(next[l]);
            }
        }
        while (r-1 >= q.r) {
            if (r-prev[r] >= l) {
                stat.remove(prev[r]);
            }
            --r;
        }
        answer[q.id] = stat.solve();
    }
    
    for (auto& it : answer) {
        std::cout << it << '\n';
    }
    return 0;
}