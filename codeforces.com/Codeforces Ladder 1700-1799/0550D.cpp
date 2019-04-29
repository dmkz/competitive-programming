/*
    Problem: 550D. Regular Bridge
    
    Solution: graphs, bridges, constructive, O(k^2 * log(k))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::set<int> si;
typedef std::vector<si> vsi;
typedef std::pair<int,int> pii;
typedef std::vector<pii> vpii;
vsi make_half(int k) {
    vsi res(k+3);
    for (int i = 1; i <= k+1; ++i) {
        for (int j = i+1; j <= k+1; ++j) {
            res[i].insert(j);
            res[j].insert(i);
        }
    }
    for (int i = 1; i <= k+1; ++i) {
        assert(isz(res[i]) == k);
    }
    const int t = k+2;
    for (int i = 1, j = k+1; isz(res[t]) != k-1 && i < j; ++i,--j) {
        res[i].erase(j);
        res[j].erase(i);
        res[i].insert(t);
        res[j].insert(t);
        res[t].insert(i);
        res[t].insert(j);
    }
    return res;
}
vpii make_graph(int k) {
    vsi fi = make_half(k);
    vsi se = make_half(k);
    vpii res;
    for (int i = 1; i < isz(fi); ++i) {
        for (int j : fi[i]) {
            int a = std::min(i,j);
            int b = std::max(i,j);
            res.push_back(pii(a, b));
        }
    }
    for (int i = 1; i < isz(se); ++i) {
        for (int j : se[i]) {
            int a = std::min(i,j) + isz(fi) - 1;
            int b = std::max(i,j) + isz(fi) - 1;
            res.push_back(pii(a, b));
        }
    }
    {
        int a = isz(fi) - 1;
        int b = 2 * isz(fi) - 2;
        res.push_back(pii(a,b));
    }
    std::sort(all(res));
    res.erase(std::unique(all(res)), res.end());
    return res;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int k;
    while (std::cin >> k) {
        if (k == 1) {
            std::cout << "YES\n";
            std::cout << "2 1\n";
            std::cout << "1 2\n";
        } else if (k % 2 == 0) {
            std::cout << "NO\n";
        } else {
            auto res = make_graph(k);
            int n = 0;
            for (auto &it : res) {
                n = std::max(n, std::max(it.first, it.second));
            }
            std::cout << "YES\n";
            std::cout << n << ' ' << isz(res) << '\n';
            for (auto &it : res) {
                std::cout << it.first << ' ' << it.second << '\n';
            }
        }
    }
    return 0;
}