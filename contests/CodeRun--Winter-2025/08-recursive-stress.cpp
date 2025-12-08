#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vi = std::vector<int>;
int count(vi a, bool debug = false) {
    std::sort(all(a), std::greater<>());
    vi used;
    int res{};
    std::function<void(int,int)> dfs = [&](int p, int sum) {
        if (p == isz(a)) {
            if (sum == 0) {
                bool ok = true;
                for (int i = 0; i < isz(a); i++)
                    if (a[i] < used[i]) {
                        ok = false;
                        break;
                    }
                if (ok) {
                    res++;
                    for (int i = 0; i < isz(a); i++)
                        a[i] -= used[i];
                }
            }
            return;
        }
        for (int x = sum; x >= 0; x--) {
            if (a[p] >= x) {
                used[p] = x;
                dfs(p+1, sum - x);
                used[p] = 0;
            }
        }
    };
    for (int sum = 1; sum <= 5; sum++) {
        used.assign(isz(a), 0);
        dfs(0, sum);
        while (isz(a) && a.back() == 0)
            a.pop_back();
        if (debug){
            std::cout << "After Step #" << sum << ":\n";
            std::cout << "    a:";
            for (auto it : a) std::cout << ' ' << it;
            std::cout << ", res = " << res << std::endl;
        }
    }
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
struct Brute {
    
    int number{};
    vi curr{};
    std::pair<int, vi> answ{};
    
    Brute(int x) : number(x) { }
    
    auto solve() {
        dfs(2, number);
        return answ;
    }
    
    void dfs(int start, int prod) {
        if (prod == 1) {
            answ = std::max(answ, std::make_pair(isz(curr), curr));
            return;
        }
        for (int x = start; x <= prod; x++)
            if ((curr.empty() || x > curr.back()) && prod % x == 0) {
                curr.push_back(x);
                dfs(x+1, prod / x);
                curr.pop_back();
            }
    }
};
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
        // Проверка что быстрое решение совпадает с брутфорсом:
        //Brute brute(x);
        //auto [k, a] = brute.solve();
        //if (k != maxCnt[x]) {
        //    std::cout << "Wrong answer!" << std::endl;
        //    std::cout << " x = " << x << std::endl;
        //    std::cout << "ft = " << maxCnt[x] << std::endl;
        //    std::cout << "sl = " << k << std::endl;
        //    std::cout << " a =";
        //    for (auto it : a) std::cout << ' ' << it;
        //    std::cout << std::endl;
        //    std::exit(0);
        //}
        //if (x % 100 == 0) {
        //    std::cout << "x = " << x << ": OK" << std::endl;
        //}
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
void research() {
    int x = 1728; // 2^6 * 3^3
    // 2 3 4 8 9: 2 * 3, осталось 2^5 * 3^2
    //            2^2, 2*3, осталось 2^2 * 3
    assert(x == 27 * 64);
    vi divs;
    factor(x, divs);
    std::cout << "divs:";
    for (auto it : divs) std::cout << ' ' << it;
    std::cout << std::endl;
    count(divs, true);
    std::exit(0);
}
main() {
    //research();
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; //std::cin >> tt;
    while (tt --> 0) solve();
}
