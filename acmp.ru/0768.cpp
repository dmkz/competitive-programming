// геометрия, прямоугольники, бинарный поиск, угол между векторами, O(n^3 log(n))
#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using pii = pair<int, int>;
using vpii = vector<pii>;
pii operator-(const pii &a, const pii &b) {
    return pii(a.first - b.first, a.second - b.second);
}
pii operator+(const pii &a, const pii &b) {
    return pii(a.first + b.first, a.second + b.second);
}
int dot(const pii &a, const pii &b) {
    return a.first * b.first + a.second * b.second;
}
bool isAngle90(const pii &a, const pii &b) {
    return dot(a, b) == 0;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vpii p(n);
    for (auto &[x,y] : p)
        cin >> x >> y;
    std::sort(all(p));
    auto count = [&](const pii &pt) {
        auto [fi,se] = std::equal_range(all(p), pt);
        return int(se - fi);
    };
    int answ{};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (j != i && p[j] != p[i]) {
            for (int k = 0; k < n; k++) {
                if (k == i || k == j || p[k] == p[i] || p[k] == p[j])
                    continue;
                if (!isAngle90(p[j] - p[i], p[k] - p[i]))
                    continue;
                // p[j] - p[i] == p[t] - p[k] => p[t] = p[j] - p[i] + p[k]
                answ += count(p[j] - p[i] + p[k]);
            }
        }
    }
    cout << answ / 8 << endl;
}
