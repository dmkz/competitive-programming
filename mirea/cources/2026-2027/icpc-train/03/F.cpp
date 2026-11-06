#include <bits/stdc++.h>
#include <bits/extc++.h>
using ll = long long;
#define int ll
using ld = long double;
using namespace std;
template<typename T> using PQLess = priority_queue<T, vector<T>, greater<T>>;
void solve() {
    // можно просто для каждой позиции найти максимальную гору слева (гору с наибольшим углом), потом
    // подставлять значение (b/a) в неравенство. Если для максимума верно, то и для любого другого верно.
    // hj < hi+(xi−xj) * b/a
    // hj-hi < (xi-xj) * (b/a)
    // (hj-hi)/(xi-xj) < (b/a)
    // (hj-hi)/(xi-xj) -> максимум при j < i
    // (h[j2] - h[i])/(x[i] - x[j2]) < (h[j1] - h[i]) / (x[i] - x[j1])
    // (h[j2] - h[i])/(x[j2] - x[i]) > (h[j1] - h[i]) / (x[j1] - x[i])
    // нужно построить выпуклую оболочку и тогда мы найдём максимум для текущей вершины как
    // предыдущую вершину в выпуклой оболочке
    int n; cin >> n;
    vector<int> x(n), h(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> h[i];
    // строим выпуклую оболочку
    auto isLess = [&](int a, int b, int c, int d) {
        return (h[b] - h[a]) * 1LL * (x[d] - x[c]) <= (h[d] - h[c]) * (x[b] - x[a]);
    };
    vector<int> st{0}, prev(n, -1);
    for (int k = 1; k < n; k++) {
        while (st.size() > 1u) {
            int i = st[st.size()-2u], j = st[st.size()-1u];
            if (isLess(i, j, i, k))
                st.pop_back();
            else break;
        }
        prev[k] = st.back();
        st.push_back(k);
    }
    // теперь читаем запросы и отслеживаем моменты, когда вершины становятся освещёнными
    // события двух типов: 1) вершина становится освещённой - FLIP, 2) нужно ответить на запрос - ASK
    // события первого типа:
    int answ = 1; // первая вершина всегда освещена
    using State = tuple<ld, int, int>;
    const int FLIP = 1, ASK = 0;
    PQLess<State> pq;
    for (int k = 1; k < n; k++) {
        const int i = prev[k];
        pq.push(State{ld(h[i]-h[k])/(x[k]-x[i]), FLIP, k});
    }
    // события второго типа:
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        pq.push(State{ld(b)/a, ASK, i});
    }
    // теперь обрабатываем события первого и второго типов в порядке возрастания угла:
    vector<int> answer(q);
    while (pq.size()) {
        auto [_, t, id] = pq.top(); pq.pop();
        if (t == FLIP) answ++;
        else { assert(t == ASK); answer[id] = answ; }
    }
    for (auto it : answer) cout << it << ' ';
    cout << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
