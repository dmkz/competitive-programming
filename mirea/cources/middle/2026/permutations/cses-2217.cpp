#include <bits/stdc++.h>
using namespace std;
main() {
    // читаем элементы и запоминаем, на каких позициях они стоят:
    int n, m;
    cin >> n >> m;
    vector<int> p(n), posOf(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        posOf[p[i]] = i;
    }
    // считаем первоначальный ответ:
    int cntLess = 0;
    for (int i = 1; i < n; i++)
        cntLess += (posOf[i-1] > posOf[i]);
    // обрабатываем запросы, обновляя ответ после каждого запроса:
    while (m --> 0) {
        int i, j; cin >> i >> j;
        i--, j--;
        int pi = p[i], pj = p[j];
        // собираем индексы элементов сравнений, в которых присутствуют pi и pj:
        set<int> s;
        // {pi, pi+1, pj, pj+1}
        for (int item : {pi, pi+1, pj, pj+1})
            if (0 <= item - 1 && item < n)
                s.insert(item);
        // обнуляем сравнения, в которых присутствуют элементы pi и pj:
        for (int pos : s)
            cntLess -= (posOf[pos] < posOf[pos-1]);
        // меняем pi и pj местами:
        swap(p[i], p[j]);
        posOf[pi] = j;
        posOf[pj] = i;
        // добавляем обновлённые сравнения в ответ:
        for (int pos : s)
            cntLess += (posOf[pos] < posOf[pos-1]);
        // выводим ответ:
        cout << cntLess + 1 << '\n';
    }
}
