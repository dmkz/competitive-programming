#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vi = std::vector<int>;
int count(vi a) {
    std::sort(all(a), std::greater<>());
    int res = isz(a);
    for (auto &it : a)
        it--;
    while (isz(a) && a.back() == 0)
        a.pop_back();
    for (int i = 0; i < isz(a); i++)
        for (int j = i; j < isz(a); j++) {
            if (a[i] > 0) {
                a[i]--;
                if (a[j] > 0) {
                    a[j]--;
                    res++;
                } else {
                    a[i]++;
                }
            }
        }
    while (isz(a) && a.back() == 0)
        a.pop_back();
    for (int i = 0; i < isz(a); i++)
        for (int j = i; j < isz(a); j++)
            for (int k = j; k < isz(a); k++) {
                if (a[i] > 0) {
                    a[i]--;
                    if (a[j] > 0) {
                        a[j]--;
                        if (a[k] > 0) {
                            a[k]--;
                            res++;
                            continue;
                        }
                        a[j]++;
                    }
                    a[i]++;
                }
            }
    while (isz(a) && a.back() == 0)
        a.pop_back();
    for (int i = 0; i < isz(a); i++)
        for (int j = i; j < isz(a); j++)
            for (int k = j; k < isz(a); k++)
                for (int t = k; t < isz(a); t++) {
                    if (a[i] > 0) {
                        a[i]--;
                        if (a[j] > 0) {
                            a[j]--;
                            if (a[k] > 0) {
                                a[k]--;
                                if (a[t] > 0) {
                                    a[t]--;
                                    res++;
                                    continue;
                                }
                                a[k]++;
                            }
                            a[j]++;
                        }
                        a[i]++;
                    }
                }
    while (isz(a) && a.back() == 0)
        a.pop_back();
    for (int i = 0; i < isz(a); i++)
        for (int j = i; j < isz(a); j++)
            for (int k = j; k < isz(a); k++)
                for (int t = k; t < isz(a); t++)
                    for (int m = t; m < isz(a); m++) {
                        if (a[i] > 0) {
                            a[i]--;
                            if (a[j] > 0) {
                                a[j]--;
                                if (a[k] > 0) {
                                    a[k]--;
                                    if (a[t] > 0) {
                                        a[t]--;
                                        if (a[m] > 0) {
                                            a[m]--;
                                            res++;
                                            continue;
                                        }
                                        a[t]++;
                                    }
                                    a[k]++;
                                }
                                a[j]++;
                            }
                            a[i]++;
                        }
                    }
    while (isz(a) && a.back() == 0)
        a.pop_back();
    return res;
}
void factor(int x, vi &divs) {
    divs.clear();
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            divs.push_back(1);
            x /= i;
            while (x % i == 0) {
                divs.back()++;
                x /= i;
            }
        }
    }
    if (x > 1)
        divs.push_back(1);
}
void solve() {
    // 2^3 * 3^2 * 5
    // сначала простые числа: 2 * 3 * 5
    // осталось: 2^2 * 3^1 = 6
    // 2^18 * 3^3 * 5 = (2 * 3 * 5) * (2 * 3) * 2^2
    // 2^14 * 3 = 2^3 * (2^2 * 3)
    // 2^9 = 2^4 * 2^5
    const int XMAX = 700000;
    std::vector<int> maxCnt(XMAX+1);
    int mx = 0;
    vi divs;
    for (int x = 2; x <= XMAX; x++) {
        divs.clear();
        factor(x, divs);
        maxCnt[x] = count(divs);
        mx = std::max(mx, maxCnt[x]);
    }
    std::vector s(mx+1, std::vector(XMAX+1, 0));
    for (int i = 0; i <= mx; i++)
        for (int x = 1; x <= XMAX; x++)
            s[i][x] = s[i][x-1] + (maxCnt[x] == i);
    int q; std::cin >> q;
    while (q --> 0) {
        int k, L, R; std::cin >> k >> L >> R;
        // все числа у которых maxCnt >= k нам подходят
        int res = 0;
        for (int i = k; i <= mx; i++)
            res += s[i][R] - s[i][L-1];
        std::cout << res << "\n";
    }
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; //std::cin >> tt;
    while (tt --> 0) solve();
}
