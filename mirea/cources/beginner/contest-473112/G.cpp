#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

using namespace std;
using ll = long long;
using vl = vector<ll>;

ll solveGreaterEqual(const vl &a, ll x, ll k) {
// кол-во пар чисел, между которыми >= k чисел, которые делятся на x
    ll answ{};
    for (int i = 0; i < isz(a); i++) {
        ll next = (a[i] + x - 1) / x * x + (k-1) * x;
        auto begin = lower_bound(all(a), a[i]);
        // все числа, которые >= next, подходят
        answ += a.end() - lower_bound(begin, a.end(), next);
    }
    return answ;
}
ll solveEqual(vl a, ll x, ll k) {
    sort(all(a));
    if (k == 0) {
        ll answ = 0;
        for (int i = 0; i < isz(a); i++) {
            // все пары a[j] < a[i] подходят
            // все a[j]: a[j] >= a[i] && a[j] < next
            auto begin = lower_bound(all(a), a[i]);
            ll next = (a[i] + x - 1) / x * x;
            answ += (a.end() - begin);
            answ -= (a.end() - lower_bound(begin, a.end(), next));
        }
        return answ;
    }
    return solveGreaterEqual(a,x,k) - solveGreaterEqual(a,x,k+1);
}
int main() {
    ll n, x, k; cin >> n >> x >> k;
    vl a(n); for (auto &it : a) cin >> it;
    cout << solveEqual(a,x,k) << endl;
}
