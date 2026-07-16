#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
int lowpos(const auto &v, const auto &x) { return int(lower_bound(all(v), x) - v.begin()); }
void setmax(auto &x, const auto &y) { if (x < y) x = y; }

void solve() {
    // читаем запросы, собираем множество используемых координат:
    int n, q; cin >> n >> q;
    vector<pair<int,int>> queries(q);
    vector<int> x = {1, n+1};
    for (auto &[l, r] : queries) {
        char c; cin >> c >> l >> r;
        x.push_back(l);
        x.push_back(r+1);
    }
    // делаем сжатие координат:
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    // отмечаем, какие отрезки заняты после всех запросов:
    const int numSegments = isz(x)-1;
    vector<int> occupied(numSegments, 0);
    for (auto &[l, _] : queries) {
        l = lowpos(x, l);
        occupied[l] = 1;
    }
    // строим двусвязный список занятых отрезков и находим лучший ответ
    // после всех запросов:
    vector<int> Prev(numSegments, -1), Next(numSegments, numSegments);
    int best = 0;
    int prevOccupied = -1;
    for (int i = 0; i < numSegments; i++) {
        if (!occupied[i])
            continue;
        setmax(best, x[i] - x[prevOccupied+1]);
        Prev[i] = prevOccupied;
        if (prevOccupied != -1)
            Next[prevOccupied] = i;
        prevOccupied = i;
    }
    setmax(best, x[numSegments] - x[prevOccupied+1]);
    // начинаем обрабатывать запросы в обратном порядке
    // теперь один запрос [l, r] удаляет один занятый отрезок и соединяет
    // два соседних свободных промежутка в один
    vector<int> answ(isz(queries));
    for (int queryId = isz(queries)-1; queryId >= 0; queryId--) {
        // текущее состояние соответствует ответу после queryId-го запроса
        // в исходном порядке, поэтому сохраняем best до "отката":
        answ[queryId] = best;
        // удаляем текущий занятый отрезок:
        int i = queries[queryId].first;
        // соседи справа и слева среди ещё занятых отрезков:
        int ni = Next[i], pi = Prev[i];
        // связываем соседей друг с другом, удаляя i:
        if (pi != -1)
            Next[pi] = ni;
        if (ni != numSegments)
            Prev[ni] = pi;
        // новый свободный промежуток ограничен занятыми соседями:
        setmax(best, x[ni] - x[pi+1]);
    }
    // выводим ответ:
    for (int i = 0; i < isz(answ); i++)
        cout << answ[i] << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}