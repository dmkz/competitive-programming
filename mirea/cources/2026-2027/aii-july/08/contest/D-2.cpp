// Прочитаем все числа, которые когда-либо появятся в множестве, и отсортируем их. Затем
// рассмотрим запросы в обратном порядке: каждая вставка теперь станет удалением. Медиану
// полного множества легко найти в отсортированном массиве. При удалении одного числа
// нижняя медиана сдвигается не более чем на одного соседа. Соседей храним в двусвязном
// списке, реализованном двумя массивами Prev и Next.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем начальные числа и запросы:
    int n, q; cin >> n >> q;
    vector<int> initial(n), queries(q), x;
    for (int i = 0; i < n; i++) {
        cin >> initial[i];
        x.push_back(initial[i]);
    }
    for (int i = 0; i < q; i++) {
        cin >> queries[i];
        x.push_back(queries[i]);
    }
    // сортируем все числа, которые будут в множестве после последней вставки:
    sort(x.begin(), x.end());
    // строим двусвязный список отсортированных чисел:
    vector<int> Prev(n + q, -1), Next(n + q, -1);
    for (int i = 0; i + 1 < n + q; i++)
        Prev[i+1] = i, Next[i] = i+1;
    // в полном множестве находим нижнюю медиану:
    int median = (n + q - 1) / 2;
    vector<int> answ(q);
    // обрабатываем запросы с конца: вставка превращается в удаление:
    for (int queryId = q-1; queryId >= 0; queryId--) {
        // текущая нижняя медиана и есть ответ после этой вставки:
        answ[queryId] = x[median];
        // находим элемент, который теперь нужно удалить:
        int xi = int(lower_bound(x.begin(), x.end(), queries[queryId]) - x.begin());
        int size = n + queryId + 1;
        // сдвигаем медиану до удаления, если её ранг изменится:
        if (size % 2 == 0 && xi <= median)
            median = Next[median];
        if (size % 2 == 1 && xi >= median)
            median = Prev[median];
        // связываем соседей друг с другом, удаляя xi:
        int pi = Prev[xi], ni = Next[xi];
        if (pi != -1) Next[pi] = ni;
        if (ni != -1) Prev[ni] = pi;
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