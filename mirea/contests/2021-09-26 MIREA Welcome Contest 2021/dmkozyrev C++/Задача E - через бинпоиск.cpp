// Решение: сортировка, бинарный поиск, O(n^2*log(n))
// Ссылка на сабмит: https://codeforces.com/group/LB1sSRhotq/contest/346286/submission/129986020
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
void setmin(auto &x, auto y) { x = (x < y ? x : y); }
using ll = long long;
const ll INF = (ll)1e18L;
int main() {
    int tt; std::cin >> tt;
    while (tt --> 0) {
        // читаем данные
        int n; std::cin >> n;
        std::vector<int> a(n);
        for (auto &it : a) std::cin >> it;
        // требуемая хрень выглядит как *****[****|***]****
        // где [ - начало префикса, | - линия разделения,
        // ] - конец суффикса, * - элементы массива
        // переберем, где будет линия разделения - это n-1 вариант
        // для каждой такой линии вычислим всех суффиксы (вправо) и все префиксы (влево)
        // суммарно суффиксов и префиксов n штук
        // отсортируем вектор из суффиксов и для каждого префикса будем искать
        // ближайший по значению суффикс бинарным поиском
        ll answ = INF;
        std::vector<ll> vec;
        for (int mid = 0; mid + 1 < n; mid++) {
            // mid - линия разделения
            // считаем все суффиксы и складываем в вектор + сортируем:
            vec = {-INF,+INF};
            ll suff{0};
            for (int i = mid + 1; i < n; i++) {
                suff += a[i];
                vec.push_back(suff);
            }
            std::sort(all(vec));
            // для каждого префикса ищем ближайший суффикс бинпоиском:
            ll pref{0};
            for (int i = mid; i >= 0; i--) {
                pref += a[i];
                auto it = std::lower_bound(all(vec),pref);
                setmin(answ,std::min(std::abs(pref-*it),std::abs(pref-*(it-1))));
            }
        }
        // выводим ответ:
        std::cout << answ << '\n';
    }
}