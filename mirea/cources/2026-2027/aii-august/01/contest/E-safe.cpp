// Сделаем бинарный поиск по величине x - скорости поедания сладостей. Для каждой сладости
// посчитаем время, необходимое для её поедания. Если x > v[i], то время равно:
// d[i] / (x - v[i]). Иначе мы никогда не закончим есть сладость и время равно бесконечности.
// В полученном массиве найдём подотрезок длины k минимальной суммы (с минимальным суммарным
// временем). Если его сумма <= t, то данная скорость подходит, иначе - нет.
// Чтобы не заморачиваться с минимальным отрезком, данное решение проверяет каждый отрезок
// длины k и находит первый из них с суммой <= t. Так тоже можно.
// Отличие безопасного решения "E-safe.cpp" от опасного "E-dangerous.cpp" в том, что мы 
// добавляем разрезание исходного массива на подотрезки, на которых нет бесконечностей.
#include <bits/stdc++.h>
#include <cassert>
#define isz(x) (int)(x).size()
using namespace std;
using ll = long long;
using ld = double;
// вспомогательная функция, которая проверяет, есть ли в массиве "a" подотрезок длины "k" с
// суммой <= t?
bool checkWindowSumK(const auto &a, int k, ld t) {
    if (k > (int)a.size())
        return false;
    // считаем и проверяем сумму в первом подотрезке длины k:
    ld s = 0;
    for (int i = 0; i < k; i++)
        s += a[i];
    if (s <= t)
        return true;
    // двигаем окно длины k вправо, считая и проверяя каждое:
    for (int i = k; i < (int)a.size(); i++) {
        s += a[i];
        s -= a[i-k];
        if (s <= t)
            return true;
    }
    return false;
}
void solve() {
    // читаем входные данные:
    int n, k; ll t; cin >> n >> k >> t;
    vector<int> d(n), v(n);
    for (int i = 0; i < n; i++)
        cin >> d[i];
    for (int i = 0; i < n; i++)
        cin >> v[i];
    // делаем бинарный поиск по скорости поедания
    // функция проверки выбранной скорости x:
    auto check = [&](ld x) {
        // для каждой сладости посчитаем время, необходимое для её поедания на фиксированной
        // скорости x. Отрезку ответа запрещено содержать сладости с x <= v[i], поэтому мы
        // разрежем исходный вектор на множество подходящих векторов:
        vector<vector<ld>> segments(1);
        for (int i = 0; i < n; i++) {
            if (x <= v[i]) {
                segments.push_back({});
                continue;
            }
            segments.back().push_back(d[i] / (x - v[i]));
        }
        // для каждого вектора решаем задачу отдельно:
        for (const auto &ss : segments)
            if (checkWindowSumK(ss, k, (ld)t))
                return true;
        return false;
    };
    // запускаем бинарный поиск на полуинтервале (0, inf]:
    ld low = 0, high = 1e12+10;
    for (int iter = 0; iter < 60; iter++) {
        ld mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid;
    }
    // выводим ответ:
    cout << setprecision(10) << fixed << high << "\n";
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
