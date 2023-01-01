// tags: math, combinatorics, permutations, O(n log(n))
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
const ll INF = (ll)1e18+100;
// предподсчитываем все факториалы:
const int NMAX = 300300;
const vl fact = [](){
    vl res(1+NMAX, 1);
    for (int i = 2; i <= NMAX; i++) {
        if (res[i-1] <= INF / i) {
            res[i] = res[i-1] * i;
        } else {
            res[i] = INF;
        }
    }
    return res;
}();
// решение задачи:
vl solve(int n, ll kk) {
    // какие числа не задействованы и их сумма:
    set<int> available;
    ll sum{};
    for (int i = 1; i <= n; i++) {
        available.insert(i);
        sum += i;
    }
    vl res(n);
    std::function<void(int,ll)> dfs = [&](int p, ll k) {
        // если k == fact[n-p], то возможны все перестановки
        if (k == fact[n-p]) {
            for (int i = p; i < n; i++)
                res[i] += fact[n-p-1] * sum;
            return;
        }
        // мы будем перебирать элемент, с которого начинается перестановка
        // учитывать его min(k, fact[n-p-1]) раз и вызываться рекурсивно
        int curr = 0;
        while (k > 0) {
            curr = *available.upper_bound(curr);
            ll delta = std::min(fact[n-p-1], k);
            k -= delta;
            // текущий элемент в текущем столбце участвует `delta` раз:
            // поставим его на все эти позиции:
            available.erase(curr);
            sum -= curr;
            res[p] += curr * delta;
            // вызываемся рекурсивно:
            dfs(p+1, delta);
            // возвращаемся из рекурсии, возвращая всё, как было:
            sum += curr;
            available.insert(curr);
        }
        
    };
    dfs(0,kk);
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; ll k;
        cin >> n >> k;
        for (auto it : solve(n,k))
            cout << it << ' ';
        cout << '\n';
    }
}