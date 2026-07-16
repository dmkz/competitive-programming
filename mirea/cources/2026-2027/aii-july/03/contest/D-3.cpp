#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
void solve() {
    // читаем запросы и запоминаем использованные координаты:
    int q; cin >> q;
    vector<int> x = {-1000000000, 1000000000};
    vector<int> queries(q);
    for (int i = 0; i < q; i++) {
        int xi; cin >> xi;
        queries[i] = xi;
        x.push_back(xi);
    }
    // сортируем координаты
    sort(all(x));
    // считаем количество каждого числа методом двух указателей:
    vector<int> cnt;
    for (int i = 0, j; i < isz(x); i = j) {
        // двигаем правую границу подотрезка равных элементов:
        for (j = i; j < isz(x) && x[i] == x[j]; j++);
        // полуинтервал [i, j) состоит из чисел, равных x[i]
        cnt.push_back(j - i);
    }
    // удаляем повторы:
    x.erase(unique(all(x)), x.end());
    // строим двусвязный список:
    vector<int> Prev(isz(x), -1), Next(isz(x), -1);
    for (int i = 0; i + 1 < isz(x); i++)
        Prev[i+1] = i, Next[i] = i+1;
    // теперь обрабатываем запросы в обратном порядке
    // каждый запрос удаляет ранее добавленный элемент
    vector<int> answ(q);
    for (int queryId = q-1; queryId >= 0; queryId--) {
        // находим и удаляем текущий элемент:
        int xi = int(lower_bound(all(x), queries[queryId]) - x.begin());
        cnt[xi]--;
        if (cnt[xi] > 0) // остался повтор
            answ[queryId] = 0;
        else {
            // соседи справа и слева:
            int ni = Next[xi], pi = Prev[xi];
            // расстояние: это минимум из расстояний до соседей:
            answ[queryId] = min(x[ni] - x[xi], x[xi] - x[pi]);
            // связываем соседей друг с другом, удаляя xi:
            Prev[ni] = pi, Next[pi] = ni;
        }
    }
    // выводим ответ:
    for (int i = 0; i < q; i++)
        cout << answ[i] << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
