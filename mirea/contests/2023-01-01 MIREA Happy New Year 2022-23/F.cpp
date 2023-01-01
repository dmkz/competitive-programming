// tags: recursion, math, O(q*log(n))
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll sign(ll x) {
    return x < 0 ? -1 : (x > 0 ? +1 : 0);
}
ll solve(ll L, ll R, ll xL, ll xR, ll p) {
// решаем для отрезка [L, R], значения на концах
// которого равны xL и xR, а позиция элемента - p
    swap(xL, xR); // сортировка
    // для отрезка длины 1 всё уже знаем:
    if (L == R) return xL;
    // где будет стоять середина отрезка:
    ll mid = (L+R)/2;
    // сколько элементов попадут в левую половину:
    ll leftHalf = mid - L + 1;
    // какое значение будет соответствовать точке в середине отрезка:
    ll xMid = xL + sign(xR-xL) * (mid - L);
    // рекурсивный вызов в зависимости от того, в какую половину мы попали:
    return (p < leftHalf) ? solve(L,mid,xL,xMid,p)
                          : solve(mid+1,R,xMid+sign(xR-xL),xR,p-leftHalf);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(4);
    int tt; cin >> tt;
    while (tt--) {
        ll L, R; int q;
        cin >> L >> R >> q;
        while (q--) {
            ll x; cin >> x;
            // удобнее решать для отрезка [0, R-L] вместо [L, R]:
            cout << L+solve(0,R-L,R-L,0,x-1) << ' ';
        }
        cout << '\n';
    }
}