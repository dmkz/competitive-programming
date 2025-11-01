// Задача: K, Вердикт: ОК, Время: 0.463 ms, Память: 97.20 МБ

#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <fstream>
#include <map>
#include <functional>
#define int int64_t
#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()
// using namespace std;
using Query = std::tuple<int, int, int, int, int, int>;
void reuniq(auto & x) {
    x.erase(std::unique(all(x)), x.end());
}

int lowpos(const auto & v, const auto & x) {
    return std::lower_bound(all(v), x) - v.begin();
}

struct Fenwick {
    std::vector<int> data;
    Fenwick(int n) : data(n, 0) { }
    void add(int p, int x) {
        while (p < isz(data)) {
            data[p] += x;
            p |= p + 1;
        }
    }
    int get(int r) const {
        int res = 0;
        while (r >= 0) {
            res += data[r];
            r = (r & (r + 1)) - 1;
        }
        return res;
    }
};

main() {
#ifdef LOCAL
    // std::ifstream cin("input.txt");
    // std::ofstream cout("output.txt");
    freopen("input.txt", "rt", stdin);
#else
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
#endif
    using std::cin;
    using std::cout;
    int n, q;
    cin >> n >> q;
    std::vector<Query> queries(q);
    std::vector<int>keys;
    Fenwick fenw(n + 1);
    int i = 0;
    for (auto &[t, l, r, x, cnt, id]:queries) {
        cin >> t;
        if (t == 1) {
            cin >> l >> r >> x >> cnt;
            l--, r--;
            keys.push_back(x);
        } else {
            assert(t == 2);
            cin >> l >> cnt;
            l--;
        }
        id = i++;
    }
    std::sort(all(keys));
    reuniq(keys);
    std::map<int, int> answer;
    for (auto &[t, l, r, x, cnt, id]:queries)
        if (t == 1)
            x = lowpos(keys, x);
    std::function<void(int, int, std::vector<Query> &) > solve =
    [&](int L, int R, auto & qq)
    {
        if (L + 1 == R) {
            for (auto &[t, l, r, x, cnt, id]:qq)
                if (t == 2)
                    answer[id] = keys[L];
            return;
        }
        if (L + 1 > R)
            return;
        int mid = (L + R) / 2;
        std::vector<Query> left, right;
        for (const auto &[t, l, r, x, cnt, id]:qq) {
            if (t == 1) {
                if (x < mid)
                    left.emplace_back(t, l, r, x, cnt, id);
                else
                    right.emplace_back(t, l, r, x, cnt, id);
            }
            if (t == 1 && x < mid) {
                fenw.add(l, +cnt);
                fenw.add(r + 1, -cnt);
            } else if (t == 2) {
                int currCnt = fenw.get(l);
                if (cnt > currCnt)
                    // справа
                    right.emplace_back(t, l, r, x, cnt - currCnt, id);
                else
                    left.emplace_back(t, l, r, x, cnt, id);
            }
        }
        for (const auto &[t, l, r, x, cnt, id]:qq)
            if (t == 1 && x < mid) {
                fenw.add(l, -cnt);
                fenw.add(r + 1, +cnt);
            }

        qq.clear();
        solve(L, mid, left);
        solve(mid, R, right);
    };
    solve(0, isz(keys), queries);
    for (const auto &[_, x]:answer)
        cout << x << "\n";
}
