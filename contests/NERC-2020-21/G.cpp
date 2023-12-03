#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n, k; cin >> n >> k;
        vi parent(1+n);
        vvi next(1+n);
        for (int i = 2; i <= n; i++) {
            cin >> parent[i];
            next[parent[i]].push_back(i);
        }
        // вычисляем высоту каждого поддерева
        vi height(1+n, 0);
        function<void(int)> dfs = [&](int u) {
            height[u] = 1;
            for (int v : next[u]) {
                dfs(v);
                setmax(height[u], height[v] + 1);
            }
            // сортируем поддеревья по убыванию высоты
            stable_sort(all(next[u]), [&](int lt, int rt) {
                return height[lt] > height[rt];
            });
        };
        dfs(1);
        // в дереве нужно оставить k вершин (ричём вершины на макс пути вниз
        // должны остаться в полном составе). Все остальные не нужны
        vi useful(1+n);
        int nUseful = 0;
        function<void(int)> select = [&](int u) {
            if (nUseful >= k)
                return;
            useful[u] = 1;
            nUseful++;
            for (int v : next[u])
                select(v);
        };
        select(1);
        // теперь ревёрсим все списки смежности и посещаем вершины в обратном порядке
        for (int u = 1; u <= n; u++)
            reverse(all(next[u]));
        vi path={1};
        function<void(int)> visit = [&](int u) {
            for (int v : next[u]) {
                if (useful[v]) {
                    path.push_back(v);
                    nUseful--;
                    visit(v);
                    if (nUseful > 0)
                        path.push_back(u);
                }
            }
        };
        k--;
        nUseful--;
        visit(1);
        // выводим ответ:
        cout << isz(path)-1 << "\n";
        for (auto u : path)
            cout << u << ' ';
        cout << std::endl;
    }
}
