#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
auto &setmin(auto &x, const auto &y) { return x = (y < x ? y : x); }
using namespace std;
using pii = pair<int,int>;
using vi = vector<int>;
using vpii = vector<pii>;
const int64_t inf = (int64_t)1e18L;
struct DSU {
    vi par;
    vector<multiset<int>> data; // в каждой компоненте храним мультимножество
                                // значений иксов этой компоненты
    vector<int64_t> answer;     // ответ для каждой компоненты
    DSU(int n, const vi &x) : par(n+1), data(n+1), answer(n+1, inf)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i, data[i] = {x[i]};
    }
    int getPar(int u) { // представитель компоненты + сжатие путей
        return par[u] == u ? u : (par[u] = getPar(par[u]));
    }
    int64_t connect(pii p) {
        return connect(p.first, p.second);
    }
    int64_t connect(int u, int v) {
        // объединение двух компонент
        u = getPar(u), v = getPar(v);
        if (u == v) // уже объединены
            return answer[u];
        // к большей компоненте соединяем меньшую:
        if (data[u].size() < data[v].size())
            swap(u, v);
        for (int x : data[v]) {
            // вставляем новое значение и обновляем ответ:
            auto iter = data[u].insert(x);
            // модуль разности с предыдущим элементом:
            if (iter != data[u].end() && iter != data[u].begin())
                setmin(answer[u], *iter-*prev(iter));
            // модуль разности со следующим элементом:
            if (iter != data[u].end() && next(iter) != data[u].end())
                setmin(answer[u], *next(iter)-*iter);
        }
        par[v] = u;
        return setmin(answer[u], answer[v]);
    }
};
main() {
    // читаем данные:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int nV, nE, nQ;
    cin >> nV >> nE >> nQ;
    vi x(nV+1);
    for (int u = 1; u <= nV; u++)
        cin >> x[u];
    // читаем рёбра
    vpii edges(nE);
    for (auto &[u, v] : edges)
        cin >> u >> v;
    // читаем запросы. будем их выполнять в обратном порядке:
    // добавления вместо удалений
    vi queries(nQ);
    for (auto &id : queries)
        cin >> id, id--;
    reverse(all(queries));
    // строим dsu и выполняем все запросы:
    DSU dsu(nV, x);
    // сначала накидываем рёбра, которые никогда не будут удалены:
    auto answ = inf;
    {
        vi allEdges, removed;
        for (int i = 1; i <= nE; i++)
            allEdges.push_back(i-1);
        removed = queries;
        sort(all(removed));
        removed.erase(unique(all(removed)), removed.end());
        vi notRemoved;
        set_difference(all(allEdges), all(removed), back_inserter(notRemoved));
        for (auto id : notRemoved)
            setmin(answ, dsu.connect(edges[id]));
    }
    // теперь добавляем рёбра из запросов:
    vector<int64_t> answers = {answ};
    for (auto id : queries)
        answers.push_back(setmin(answ, dsu.connect(edges[id])));
    // выводим ответы:
    reverse(all(answers));
    for (auto &it : answers) {
        if (it >= inf)
            it = -1;
        cout << it << ' ';
    }
}
