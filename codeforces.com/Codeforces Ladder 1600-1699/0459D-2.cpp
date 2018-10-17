/*
    Problem: 459D. Pashmak and Parmida's problem
    
    Solution: divide and conquer, merge sort, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#define size(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define unique(x) (x).erase(std::unique(all(x)), (x).end())
#define binpos(x, y) int(std::lower_bound(all(x), (y)) - (x).begin())

typedef long long ll;
typedef std::vector<int> vi;

void solve(int begin, int after, vi& pref, vi& suff, ll& answ) {
    if (begin+1 >= after) {return;}
    int mid = (begin + after) / 2;
    solve(begin, mid, pref, suff, answ);
    solve(mid, after, pref, suff, answ);
    for (int i = begin, j = mid; i < mid; ++i) {
        while (j < after && pref[i] > suff[j]) ++j;
        answ += j - mid;
    }
    {
        vi temp;
        std::merge(pref.begin()+begin, pref.begin()+mid, pref.begin()+mid, pref.begin()+after, std::back_inserter(temp));
        for (int i = begin; i < after; ++i) {pref[i] = temp[i-begin];}
    }
    {
        vi temp;
        std::merge(suff.begin()+begin, suff.begin()+mid, suff.begin()+mid, suff.begin()+after, std::back_inserter(temp));
        for (int i = begin; i < after; ++i) {suff[i] = temp[i-begin];}
    }
}

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
    ll answ = 0;
    solve(0, n, pref, suff, answ);
    std::cout << answ << "\n";
    return 0;
}