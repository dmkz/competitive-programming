/*
    Problem: 459D. Pashmak and Parmida's problem
    
    Solution: fenwick tree, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

#define size(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define unique(x) (x).erase(std::unique(all(x)), (x).end())
#define binpos(x, y) int(std::lower_bound(all(x), (y)) - (x).begin())

typedef long long ll;
typedef std::vector<int> vi;

struct Fenwick {

    vi data;

    Fenwick(int n) : data(n, 0) { }
    
    void inc(int pos, int delta) {
        for (int i = pos; i < size(data); i = (i | (i+1))) {
            data[i] += delta;
        }
    }
    
    int get(int r) {
        int ret = 0;
        for (int i = r; i >= 0; i = (i & (i+1)) - 1) {
            ret += data[i];
        }
        return ret;
    }
};

int main() {
    int n; scanf("%d", &n);
    vi arr(n), item;
    for (auto& it : arr) {
        scanf("%d", &it);
        item.push_back(it);
    }
    std::sort(all(item));
    unique(item);
    for (auto& it : arr) {
        it = binpos(item, it);
    }
    vi cnt(size(item)), pref(n), suff(n);
    for (int i = 0; i < n; ++i) {
        pref[i] = ++cnt[arr[i]];
    }
    std::fill(all(cnt), 0);
    for (int i = n-1; i >= 0; --i) {
        suff[i] = ++cnt[arr[i]];
    }
    // Create Fenwick Tree:
    Fenwick fenwick(1+n);
    for (int i = 0; i < n; ++i) {
        fenwick.inc(suff[i],  1);
    }
    // Calculate answer:
    ll answ = 0;
    for (int i = 0; i < n; ++i) {
        fenwick.inc(suff[i], -1);
        answ += fenwick.get(pref[i]-1);
    }
    std::cout << answ << std::endl;
    return 0;
}