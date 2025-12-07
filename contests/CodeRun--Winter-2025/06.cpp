#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using ll = long long;

template<typename T>
struct PrefSums {
    std::vector<int> x;
    std::vector<ll> s;
    
    PrefSums(const std::vector<T> &x_) : x(x_)
    {
        // сортируем x:
        std::sort(all(x));
        // считаем префикс-суммы:
        s.push_back(0);
        for (auto it : x)
            s.push_back(s.back() + it);
    }
    ll getSum(int l, int r) const {
        // сумма на отрезке [l, r]:
        return (l > r) ? 0 : (s[r+1] - s[l]);
    }
    // сумма манхеттенский расстояний:
    ll operator()(int currX) const {
        // аккуратно раскрываем сумму модулей разности с соответствующим знаком
        // sum(|x[i] - currX|) = sum_{x[i] >  currX} (x[i] - currX) +
        //                       sum_{x[i] <= currX} (currX - x[i])
        auto mid = std::upper_bound(all(x), currX);
        int nGreaterThanX = int(x.end() - mid);     // (x[i] - currX)
        int nLessEqualToX = isz(x) - nGreaterThanX; // (currX - x[i])
        ll res = nGreaterThanX * (-1LL) * currX;
        res += nLessEqualToX * (1LL) * currX;
        int pos = int(mid - x.begin());
        res += getSum(pos, isz(x)-1);
        res -= getSum(0, pos-1);
        return res;
    }
};
void solve() {
    int nPoints, nQueries;
    std::cin >> nPoints >> nQueries;
    std::vector<int> x(nPoints), y(nPoints);
    for (int i = 0; i < nPoints; i++)
        std::cin >> x[i] >> y[i];
    PrefSums<int> sx(x), sy(y);
    int currX = 0, currY = 0;
    std::string s; std::cin >> s;
    for (auto it : s) {
        switch(it) {
            case 'N': currY++; break;
            case 'S': currY--; break;
            case 'W': currX--; break;
            case 'E': currX++; break;
            default: assert(false);
        };
        std::cout << sx(currX) + sy(currY) << "\n";
    }
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    solve();
}
