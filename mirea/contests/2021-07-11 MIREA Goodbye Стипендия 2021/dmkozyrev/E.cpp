#include <bits/stdc++.h>
using ll = long long;
ll f(ll n) {
    // Число способов выбрать пару колб из n одинаковых = C(n,2)
    return n * (n-1) / 2;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем данные и считаем сколько каких вакцин у нас есть:
    int n; std::cin >> n;
    std::vector<int> a(n),cnt(1+n);
    for (auto &it : a) {
        std::cin >> it;
        cnt[it]++;
    }
    // посчитаем ответ без удаления чего-либо. Это сумма C(cnt[i],2)
    ll answ=0;
    for (auto &it : cnt) {
        answ += f(it);
    }
    // считаем ответы с удалениями:
    for (auto it : a) {
        // из ответа без удалений необходимо вычесть C(cnt[i],2) и добавить C(cnt[i]-1,2)
        // так как i-й вакцины стало меньше на одну колбу
        // то есть пересчитать всю сумму, изменив лишь одно слагаемое:
        std::cout << answ - f(cnt[it]) + f(cnt[it]-1) << ' ';
    }
    std::cout << std::endl;
    return 0;
}