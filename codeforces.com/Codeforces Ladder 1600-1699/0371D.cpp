/*
	Problem: 371D. Vessels
	
	Solution: Sqrt-Decomposition, lower bound, O(n+q*sqrt(n))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdlib>

typedef long long ll;

struct SqrtDecomposition {

    int nItems, nGroups;

    std::vector<ll> data, gsum;

    int GSIZE;
    
    std::vector<int> gLeft, gRight;
    
    SqrtDecomposition(const std::vector<ll>& arr) {
        data = arr;
        nItems = (int)data.size();
        GSIZE = (int)std::sqrt(nItems / 2.0);
        nGroups = (nItems + GSIZE - 1) / GSIZE;
        gsum.resize(nGroups);
        gLeft.resize(nGroups);
        gRight.resize(nGroups);
        for (int g = 0; g < nGroups; ++g) {
            gLeft[g] = g * GSIZE;
            gRight[g] = std::min(nItems-1, gLeft[g] + GSIZE - 1);
            for (int i = gLeft[g]; i <= gRight[g]; ++i) {
                gsum[g] += data[i];
            }
        }
    }
    
    void push(int g) {
        assert(0 <= g && g < nGroups);
        if (gsum[g] == 0) {
            for (int i = gLeft[g]; i <= gRight[g]; ++i) {
                assert(0 <= i && i < nItems);
                data[i] = 0;
            }
        }
    }
    
    void modify(int p, ll x) {
        int g = p / GSIZE;
        assert(0 <= g && g < nGroups);
        push(g);
        for (int i = p; i <= gRight[g]; ++i) {
            assert(0 <= i && i < nItems);
            if (x >= data[i]) {
                gsum[g] -= data[i];
                x -= data[i];
                data[i] = 0;
            } else {
                data[i] -= x;
                gsum[g] -= x;
                x = 0;
                break;
            }
        }
        ++g;
        while (x > 0 && g < nGroups) {
            if (x >= gsum[g]) {
                x -= gsum[g];
                gsum[g] = 0;
            } else {
                break;
            }
            ++g;
        }
        if (x > 0) {
            assert(g < nGroups);
            push(g);
        }
        if (x == 0) {
            return;
        }
        assert(0 <= g && g < nGroups);
        for (int i = gLeft[g]; i <= gRight[g]; ++i) {
            assert(0 <= i && i < nItems);
            if (x >= data[i]) {
                gsum[g] -= data[i];
                x -= data[i];
                data[i] = 0;
            } else {
                data[i] -= x;
                gsum[g] -= x;
                x = 0;
                break;
            }
        }
        assert(x == 0);
    }
    
    ll get(int p) {
        int g = p / GSIZE;
        push(g);
        assert(0 <= p && p < nItems);
        assert(0 <= g && g < nGroups);
        return data[p];
    }

};

const ll INF = (ll)1e15L;

struct Query {
    int t, fi, se;
    
    Query(int t_ = 0, int fi_ = 0, int se_ = 0) : t(t_), fi(fi_), se(se_) { }
};

std::vector<ll> solve(std::vector<ll> arr, std::vector<Query> queries) {
    std::vector<ll> answ;
    arr.push_back(INF);
    SqrtDecomposition sd(arr);
    const int nQ = (int)queries.size();
    for (int i = 0; i < nQ; ++i) {
        int t = queries[i].t;
        if (t == 1) {
            int p = queries[i].fi-1;
            int x = queries[i].se;
            sd.modify(p,x);
        } else {
            int p = queries[i].fi-1;
            answ.push_back(arr[p] - sd.get(p));
        }
    }
    return answ;
}

int main() {    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; 
    while (std::cin >> n) {
        std::vector<ll> arr(n, INF);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        int nQ; std::cin >> nQ;
        std::vector<Query> queries(nQ);
        for (int i = 0; i < nQ; ++i) {
            int t, fi = 0, se = 0; std::cin >> t >> fi;
            if (t == 1) std::cin >> se;
            queries[i] = Query(t, fi, se);
        }
        auto answ = solve(arr, queries);
        for (auto& it : answ) { std::cout << it << "\n"; }
    }
    return 0;
}