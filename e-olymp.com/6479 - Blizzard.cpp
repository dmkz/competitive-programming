/*
    Problem: 6479. Blizzard
    
    Solution: std::priority_queue, sqrt-decomposition, binary search, O(n * sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

#define isz(x) (int)(x).size()

typedef std::vector<int> vi;

const int UNDEF = -1;

struct SD {
    int gsize;
    vi data, gset;
    template<typename T> void build(const std::vector<T>& vec) {
        data.resize(isz(vec));
        gsize = int(std::sqrt(isz(vec)));
        for (int i = 0; i < isz(vec); ++i) { data[i] = vec[i]; }
        gset.assign((isz(data) + gsize - 1) / gsize, UNDEF);
    }
    void push(int g) {
        if (gset[g] != UNDEF) {
            const int begin = g * gsize;
            const int after = std::min(begin + gsize, isz(data));
            const int x = gset[g];
            for (int i = begin; i < after; ++i) { data[i] = x; }
            gset[g] = UNDEF;
        }
    }
    void set(const int l, const int r, const int x) {
        const int gl = l / gsize, gr = r / gsize;
        push(gl);
        if (gl == gr) {
            for (int i = l; i <= r; ++i) { data[i] = x; }
        } else {
            push(gr);
            for (int i = l; i < (gl+1) * gsize; ++i) { data[i] = x; }
            for (int i = gr * gsize; i <= r; ++i) { data[i] = x; }
            for (int g = gl+1; g < gr; ++g) { gset[g] = x; }
        }
    }
    int operator[](int pos) const {
        return gset[pos / gsize] != UNDEF ? gset[pos / gsize] : data[pos];
    }
};

struct Pair { int len, id; };
bool operator<(const Pair& a, const Pair& b) { return a.len < b.len || (a.len == b.len && a.id < b.id); }
bool operator>(const Pair& a, const Pair& b) { return b < a; }
bool operator==(const Pair& a, const Pair& b) { return !(b < a || a < b); }

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int roadLength, n; std::cin >> roadLength >> n;
    vi used(n,false);
    SD left, right;
    {
        vi lt(n), rt(n);
        for (int i = 0; i < n; ++i) { std::cin >> lt[i] >> rt[i]; rt[i]--; }
        left.build(lt);
        right.build(rt);
    }
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> global;
    auto local = global;
    for (int i = 0; i < n; ++i) { global.push(Pair{right[i] - left[i] + 1, i}); }
    vi answ;
    while (isz(local) > 0 || isz(global) > 0) {
        Pair best{INT_MAX,-1};
        if (isz(local) > 0) { best = local.top(); }
        if (isz(global) > 0) { best = std::min(best, global.top()); }
        if (isz(local) > 0 && local.top() == best) { local.pop(); }
        if (isz(global) > 0 && global.top() == best) { global.pop(); }
        const int id = best.id;
        if (id == -1 || used[id]) { continue; }
        answ.push_back(id+1);
        used[id] = 1;
        const int newLeft = right[id]+1, newRight = left[id]-1;
        {
            int low = -1, high = id;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (right[mid] < newRight) { low = mid; }
                else { high = mid; }
            }
            right.set(high, id, newRight);
        }
        {
            int low = id, high = n;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (left[mid] > newLeft) { high = mid; }
                else { low = mid; }
            }
            left.set(id, low, newLeft);
        }
        if (id + 1 < n && !used[id+1]) {
            local.push(Pair{right[id+1] - left[id+1] + 1, id+1});
        }
        if (id - 1 >= 0 && !used[id-1]) {
            int low = -1, high = id-1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (left[mid] == left[id-1] && right[mid] == right[id-1]) { high = mid; }
                else { low = mid; }
            }
            assert(!used[high]);
            local.push(Pair{right[high] - left[high] + 1, high});
        }
    }
    for (auto it : answ) { std::cout << it << '\n'; }
    return 0;
}