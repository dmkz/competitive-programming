#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
void remin(auto &x, const auto &y) { if (y < x) x = y; }
using ll = long long;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using pll = std::pair<ll,ll>;
using vpll = std::vector<pll>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
const ll inf = (ll)1e18L;

// план решения:
// dp[u][color] = минимальная стоимость покрасить всё поддерево вершины u,
// причём сама вершина u будет иметь цвет color
// про покрашивание поддеревьев:
// если мы всех покрасим в цвет A, мы потратим сумму costA
// теперь мы начнём перекрашивать в цвет B, чтобы уменьшить сумму
// sum - costA + costB -> min
// sum - (costA - costB) -> min ==> (costA - costB) -> max
// вывод: надо перекрашивать в порядке убывания (costA - costB)
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) {
        // чтение дерева:
        int nV, nColors;
        std::cin >> nV >> nColors;
        vvi adj(1+nV);
        for (int i = 0; i < nV-1; i++) {
            int u, v; std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // чтение стоимостей покраски
        // у нас есть всего две различные стоимости, просто посчитаем их количество
        int costA = -1, costB = -1, cntA = -1, cntB = -1;
        for (int i = 0; i < nColors; i++) {
            int cost; std::cin >> cost;
            if (cost == costA)
                cntA++;
            else if (cost == costB)
                cntB++;
            else if (costA == -1) {
                costA = cost;
                cntA = 1;
            } else if (costB == -1) {
                costB = cost;
                cntB = 1;
            } else {
                assert(false); // невозможный случай
            }
        }
        // проверка что авторы не обманули и действительно существует два цвета:
        assert(cntA > 0 && cntB > 0);
        assert(cntA + cntB == nColors);
        // запустим динамическое программирование на дереве
        vvl dp(nV+1, vl{inf, inf});
        std::function<void(int,int)> dfs = [&](int u, int p) {
            vl subtreeRepaintingCost;
            ll usedA = 0, usedB = 0;
            ll totalSubtreeCost = 0;
            for (int v : adj[u]) {
                if (v != p) {
                    dfs(v, u);
                    subtreeRepaintingCost.emplace_back(dp[v][0]-dp[v][1]);
                    // сначала тупо красим в цвет A:
                    totalSubtreeCost += dp[v][0];
                    usedA++;
                }
            }
            // теперь для всех поддеревьев ответы вычислены
            // всех покрасили в цвет A
            // начинаем перекрашивать в цвет B самые выгодные из них
            // то есть в порядке убывания costA-costB
            std::sort(all(subtreeRepaintingCost), std::greater<>());
            auto update = [&](){
                if (usedA <= cntA && usedB <= cntB) {
                    if (usedA+1 <= cntA) // можем корень покрасить в A
                        remin(dp[u][0], totalSubtreeCost + costA);
                    if (usedB+1 <= cntB) // можем корень покрасить в B
                        remin(dp[u][1], totalSubtreeCost + costB);
                }
            };
            update();
            for (auto diff : subtreeRepaintingCost) {
                totalSubtreeCost -= diff;
                usedB++;
                usedA--;
                update();
            }
        };
        dfs(1, 0);
        std::cout << std::min(dp[1][0], dp[1][1]) << std::endl;
    }
}
