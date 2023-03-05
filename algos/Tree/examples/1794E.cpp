#include "template.hpp"
#include "segmenttreelazy.hpp"
#include "tree.hpp"
#include "hash.hpp"
using namespace algos::tree;
using namespace algos::hash;
using namespace algos::SegmentTreeLazy;
int main() {
    // предподсчитываем степени основания хеширования:
    int n; std::cin >> n;
    std::vector<Hash> powers(n, 1);
    for (int i = 1; i < n; i++)
        powers[i] = powers[i-1] * base;
    auto sorted_powers = powers;
    std::sort(all(sorted_powers));
    const Hash ibase = base^(-1);
    // считаем хеш от мультимножества a:
    Hash ha;
    for (int i = 0; i < n-1; i++) {
        int a; std::cin >> a;
        ha += powers[a];
    }
    // читаем дерево и строим эйлеров обход:
    EulerTour euler;
    auto [L,R] = euler.build(n, readEdges(n));
    auto &adj = euler.adj;
    // считаем хеш от расстояний до всех вершин когда корень = 1:
    std::vector<Hash> treeHash(n);
    std::function<void(int,int,int)> dfs = [&](int u, int p, int d) {
        treeHash[L(u)] = powers[d];
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v,u,d+1);
        }
    };
    dfs(1,0,0);
    // создаём дерево отрезков на основе посчитанных хешей:
    SegmentTree<Hash, Hash, TraitsSumMul<Hash,Hash>> segtree;
    segtree.build(treeHash);
    // находим ответ:
    vi answer;
    std::function<void(int,int)> solve = [&](int u, int p) {
        // разница между хешем от мультимножества расстояний
        // и хешем от мультимножества А должна быть одним числом
        auto diff = segtree.get(0, n-1) - ha;
        if (std::binary_search(all(sorted_powers), diff))
            answer << u;
        for (int v : adj[u]) {
            if (v == p) continue;
            // делим поддерево на base, умножаем остальное на base
            segtree.update(0, n-1, base);
            segtree.update(L(v), R(v), ibase * ibase);
            solve(v,u);
            segtree.update(L(v), R(v), base * base);
            segtree.update(0, n-1, ibase);
        }
    };
    solve(1,0);
    // выводим отсортированный ответ:
    std::cout << isz(answer) << '\n';
    std::sort(all(answer));
    for (auto it : answer)
        std::cout << it << ' ';
    std::cout << '\n';
}
