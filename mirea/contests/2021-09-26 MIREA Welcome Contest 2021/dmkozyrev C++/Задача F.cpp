// Решение: сумма в скользящем окне, O(n)
// Ссылка на сабмит: https://codeforces.com/group/LB1sSRhotq/contest/346286/submission/129987463
#include <bits/stdc++.h>

using ll = long long;
const ll INF = (ll)1e18L;

ll findMaxWindow(const auto& group, const int k) {
    // находим максимум среди всех отрезков длины k
    if (k > (int)group.size()) {
        return -INF;
    }
    // сумма в самом первом отрезке:
    ll sum = 0;
    for (int i = 0; i < k; i++) {
        sum += group[i];
    }
    ll max = sum;
    // перебираем все остальные отрезки слева-направо:
    for (int i = k; i < (int)group.size(); i++) {
        // при сдвиге отрезка вправо
        sum += group[i];   // добавляется новый элемент справа
        sum -= group[i-k]; // вычитается крайний элемент слева
        max = std::max(max,sum);
    }
    return max;
}
int main() {
    int tt; std::cin >> tt;
    while (tt --> 0) {
        int n,k,d; std::cin >> n >> k >> d;
        // читаем числа и складываем в группы
        // согласно остатку от деления их индекса на d
        std::vector<std::vector<int>> group(d);
        for (int i = 0; i < n; i++) {
            int a; std::cin >> a;
            group[i%d].push_back(a);
        }
        // находим максимум среди всех групп
        ll answ = -INF;
        for (auto &g : group) {
            answ = std::max(answ, findMaxWindow(g,k));
        }
        std::cout << answ << std::endl;
    }
}