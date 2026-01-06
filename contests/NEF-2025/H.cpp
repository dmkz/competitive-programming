// математика, наибольший общий делитель
#include <bits/stdc++.h>
using ll = long long;
ll findMaxDiv(ll a, ll b) {
// возвращает максимальное число, на которое делится как a, так и b
    return std::gcd(a, b);
}
void solve(ll w, ll h, ll d, ll n) {
    // можем найти ответ, взяв максимальные делители?
    ll a = findMaxDiv(n, w);
    ll b = findMaxDiv(n/a, h);
    ll c = n / (a * b);
    if (c <= d && d % c == 0)
        std::cout << a-1 << ' ' << b-1 << ' ' << c-1 << std::endl;
    else
        std::cout << "-1\n";
}
main() {
    ll w, h, d, n;
    std::cin >> w >> h >> d >> n;
    solve(w,h,d,n);
}
