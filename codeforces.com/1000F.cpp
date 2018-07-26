/*
    Problem: 1000F. One Occurrence

    Solution: Mo's algorithm, Sqrt-Decomposition, O(n sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

struct Statistic {
    
    std::vector<int> count, nOnes;
    
    static const int gsize = 800;
    
    Statistic(const int mxValue) 
        : count(mxValue+1, 0)
        , nOnes((mxValue + gsize) / gsize, 0) 
    { }
    
    void insert(int value) {
        count[value]++;
        if (count[value] == 1) {
            nOnes[value / gsize]++;
        }
        if (count[value] == 2) {
            nOnes[value / gsize]--;
        }
    }
    
    void remove(int value) {
        count[value]--;
        if (count[value] == 1) {
            nOnes[value / gsize]++;
        }
        if (count[value] == 0) {
            nOnes[value / gsize]--;
        }
    }
    
    int solve() const {
        int g = 0;
        while (g < (int)nOnes.size() && nOnes[g] == 0) {
            ++g;
        }
        if (g >= (int)nOnes.size()) {
            return 0;
        }
        const int begin = g * gsize;
        const int after = std::min(begin + gsize, (int)count.size());
        for (int i = begin; i < after; ++i) {
            if (count[i] == 1) {
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
    
    int n; std::cin >> n;
    
    std::vector<int> arr(n);
    
    for (auto& it : arr) {
        std::cin >> it;
    }
    
    int nQueries;
    std::cin >> nQueries;
    
    std::vector<Query> queries;
    
    for (int i = 0; i < nQueries; ++i) {
        int l, r; std::cin >> l >> r; --l, --r;
        queries.push_back(Query{l, r, i});
    }
    
    const int gsize = 800;
    
    std::sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        if (a.l / gsize == b.l / gsize) {
            return (((a.l / gsize) & 1) ? a.r < b.r : a.r > b.r);
        } else {
            return (a.l / gsize < b.l / gsize);
        }
    });
    
    
    int l = 0, r = -1;
    Statistic stat(*std::max_element(arr.begin(), arr.end()));
    
    std::vector<int> answer(nQueries);
    
    for (auto& q : queries) {
        while (r+1 <= q.r) stat.insert(arr[++r]);
        while (l+1 <= q.l) stat.remove(arr[l++]);
        while (l-1 >= q.l) stat.insert(arr[--l]);
        while (r-1 >= q.r) stat.remove(arr[r--]);
        answer[q.id] = stat.solve();
    }
    
    for (auto& it : answer) {
        std::cout << it << '\n';
    }
    
    return 0;
}