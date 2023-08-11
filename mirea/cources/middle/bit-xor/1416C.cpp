#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using ll = long long;
using pll = std::pair<ll,ll>;
using vpll = std::vector<pll>;
using vvpll = std::vector<vpll>;
using vi = std::vector<int>;
vvpll count(30);
void solve(vi &a, int bit, int L, int R) {
    if (bit < 0 || L > R)
        return;
    // если в разряде bit у числа a[i] стоит 1, а у числа a[j] стоит 0, i < j
    // то такая пара образует инверсию
    // остались только пары, у которых разряд одинаковый
    // для них инверсия может быть образована в младших битах
    // надо вызвать рекурсивно
    vi zeros, ones;
    ll n01{}, n10{};
    for (int i = L; i <= R; i++)
        if ((a[i] >> bit) & 1) {
            ones.push_back(a[i]);
            n01 += isz(zeros);
        } else {
            zeros.push_back(a[i]);
            n10 += isz(ones);
        }
    count[bit].emplace_back(n01, n10);
    int mid = L + isz(zeros) - 1;
    int i = R;
    while (isz(ones)) a[i--] = ones.back(), ones.pop_back(); 
    while (isz(zeros)) a[i--] = zeros.back(), zeros.pop_back();
    solve(a,bit-1,L,mid);
    solve(a,bit-1,mid+1,R);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем данные
    int n; std::cin >> n;
    vi a(n); for (auto &it : a) std::cin >> it;
    // вызываем предподсчёт числа инверсий
    solve(a, 29, 0, n-1);
    // находим ответ:
    ll answ{}, x{};
    for (int bit = 29; bit >= 0; bit--) {
        ll sum01{}, sum10{};
        for (auto &[n01, n10] : count[bit]) {
            // если не менять текущий разряд, то число инверсий будет numInv
            // иначе каждый 0 заменится на 1, а каждый 1 на 0
            sum10 += n10;
            sum01 += n01;
        }
        if (sum10 <= sum01) answ += sum10;
        else answ += sum01, x |= (1 << bit);
    }
    std::cout << answ << ' ' << x << std::endl;
    return 0;
}
