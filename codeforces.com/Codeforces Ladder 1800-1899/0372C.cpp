/*
    Problem: 372C. Watching Fireworks is Fun
    Solution: dynamic programming, MaxQueue, O(m*n)
*/
#include <bits/stdc++.h>
using ll = long long;
const int NMAX = 150064;
int a[300],b[300],t[300],n,m,d;
ll curr[NMAX],next[NMAX];
namespace MaxQueue {
    int begin, end; ll data[NMAX];
    void clear() { begin = end = 0; }
    void push(ll x) {
        while (end > begin && data[end-1] < x) end--;
        data[end++] = x;
    }
    void pop(ll x) { begin += (data[begin] == x); }
    ll getMax() { return data[begin]; }
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    std::cin >> n >> m >> d;
    for (int i = 0; i < m; i++) {
        std::cin >> a[i] >> b[i] >> t[i];
        a[i]--;
    }
    for (int id = 0, time = 1; id < m; id++) {
        MaxQueue::clear();
        int diff = (int)std::min((ll)n-1, ll(t[id] - time) * d);
        time = t[id];
        for (int i = 0; i <= diff; i++) MaxQueue::push(curr[i]);
        for (int i = 0; i < n; i++) {
            next[i] = MaxQueue::getMax() + b[id] - std::abs(a[id] - i);
            if (i - diff >= 0) MaxQueue::pop(curr[i-diff]);
            if (i + diff + 1 < n) MaxQueue::push(curr[i+diff+1]);
        }
        std::memcpy(curr, next, sizeof(next));
    }
    std::cout << *std::max_element(curr,curr+n) << std::endl;
    return 0;
}