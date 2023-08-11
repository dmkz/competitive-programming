#include <bits/stdc++.h>
// Operations with bits:
template<typename T> void setbit(T &mask, int bit, bool x) { (mask &= ~(T(1) << bit)) |= (T(x) << bit); }
template<typename T> bool getbit(T &mask, int bit) { return (mask >> bit & 1); }
template<typename T> void flipbit(T &mask, int bit) { mask ^= (T(1) << bit); }

using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vvpii = std::vector<vpii>;
using vi = std::vector<int>;

#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()

void remax(auto &x, const auto & y) { if (x < y) x = y; }

int main() {
    // читаем рёбра и строим списки смежности
    int nVert, root; std::cin >> nVert >> root;
    vvpii adj(1+nVert);
    for (int i = 0; i < nVert-1; i++) {
        int u, v, w; std::cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    // запускаем dfs из корня, чтобы вычислить ксор на путях от корня до каждой вершины
    vi xorPath(1+nVert);
    std::function<void(int,int)> dfs = [&](int u, int p) {
        for (auto [v,w] : adj[u]) {
            if (v == p) continue;
            xorPath[v] = (xorPath[u] ^ w);
            dfs(v, u);
        }
    };
    dfs(root, 0);
    // теперь нужно найти пару (u,v), ксор между которыми максимален
    // мы используем тот факт, что xor(u,v) = xor(u, root) ^ xor(v, root)
    // типо общий путь до корня уничтожится
    // строим двоичный бот неявно
    vi a;
    for (int u = 1; u <= nVert; u++)
        if (u != root)
            a.push_back(xorPath[u]);
    std::sort(all(a));
    // теперь ищем
    auto getMax = [&](int i, int x) {
        int L = 0, R = i-1;
        int result = 0;
        for (int bit = 30; bit >= 0; bit--) {
            // ищем первый единичный бит
            int low = L-1, high = R+1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (getbit(a[mid], bit)) high = mid;
                else low = mid;
            }
            // i-й бит у всех чисел на отрезке [L, low] равен 0
            // а на отрезке [high, R] равен 1
            if (getbit(x, bit) == 1) {
                // надо идти в отрезок, где бит равен 0
                if (L <= low) {
                    R = low;
                    flipbit(result, bit);
                }
                // иначе весь отрезок состоит из 0
            } else {
                // надо идти в отрезок, где бит равен 1
                if (high <= R) {
                    L = high;
                    flipbit(result, bit);
                }
                // иначе весь отрезок состоит из 0
            }
        }
        return result;
    };
    int answ{};
    for (int i = 1; i < isz(a); i++)
        remax(answ, getMax(i, a[i]));
    std::cout << answ << std::endl;
}
