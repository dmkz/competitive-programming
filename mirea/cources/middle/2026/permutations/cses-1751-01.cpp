#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение:
    int n; cin >> n;
    vvi t(30, vi(n+1)); // t[k][i] - хранит номер вершины, в которой мы
                        // окажемся, сделав 2^k переходов из i
    for (int i = 1; i <= n; i++)
        cin >> t[0][i]; // через 1 переход (2^0) из вершины i
    // строим таблицу двоичных прыжков:
    for (int k = 1; k < 30; k++)
        for (int i = 1; i <= n; i++) {
            // нужно посчитать, где мы окажемся через 2^k прыжков,
            // начиная в вершине i. Знаем:
            // t[k-1][i] <-- где мы окажемся через 2^(k-1) прыжков из i
            int j = t[k-1][i]; // через 2^(k-1) прыжков
            t[k][i] = t[k-1][j]; // ещё 2^(k-1) прыжков делаем
            // 2^(k-1) + 2^(k-1) = 2^k
        }
    // делаем бесконечное число переходов: 2^29:
    vi f = t[29];
    // сортируем + удаляем повторы:
    sort(all(f));
    f.erase(unique(all(f)), f.end());
    f.erase(f.begin()); // удаляем 0
    // находим ответы для всех вершин, которые лежат на циклах:
    vector<bool> used(n+1);
    vector<int> answer(n+1);
    vector<int> currCycle;
    for (int i : f)
        if (!used[i]) {
            used[i] = true;
            currCycle = {i};
            for (int j = t[0][i]; j != i; j = t[0][j]) {
                used[j] = true;
                currCycle.push_back(j);
            }
            // нашли цикл. Отмечаем номер:
            for (auto vert : currCycle)
                answer[vert] = (int)currCycle.size();
        }
    // рекурсивно найдём все остальные ответы:
    function<int(int)> findAnswer = [&](int i) {
        if (answer[i])
            return answer[i];
        return answer[i] = findAnswer(t[0][i]) + 1;
    };
    // выводим ответы:
    for (int i = 1; i <= n; i++)
        cout << findAnswer(i) << ' ';
}