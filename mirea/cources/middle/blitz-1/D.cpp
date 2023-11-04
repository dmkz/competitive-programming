#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ld = long double;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // применим бинарный поиск по ответу. Для заданного x проверим, есть ли набор
    // из k элементов такой, что sum_k(a) / sum_k(b) >= x
    // упростим выражение, ведь теперь мы знаем x, так как зафиксировали его:
    // sum_k(a) >= x * sum_k(b)
    // sum_k(a) - x * sum_k(b) >= 0
    // sum_k(a[i] - x * b[i]) >= 0
    // свели задачу к следующей: можно ли набрать сумму >= 0 из k слагаемых, имея n
    // решаем сортировкой по убыванию
    
    // читаем данные:
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i] >> b[i];
    // запускаем бинарный поиск:
    ld low = 0, high = 1e9;
    for (int iter = 0; iter < 100; iter++) {
        // фиксируем x:
        ld x = (low+high) / 2;
        // строим массив из a[i] - x * b[i]:
        vector<ld> c(n);
        for (int i = 0; i < n; i++)
            c[i] = a[i] - x * b[i];
        // сортируем его по убыванию + выбираем k максимальных слагаемых:
        sort(all(c), greater<>());
        c.resize(k);
        // проверяем, что сумма k максимальных >= 0:
        ld sum = accumulate(all(c), ld(0));
        if (sum >= 0) low = x;
        else high = x;
    }
    // выводим ответ:
    cout << fixed << setprecision(9);
    cout << low << endl;
}
