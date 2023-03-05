// problem: 1794E. Labeling the Tree with Distances
// solution: trees, re-rooting of trees, hashes of trees
#include "template.hpp"
#include "tree.hpp"
#include "hash.hpp"
#include "debug.hpp"
using namespace algos::tree;
using namespace algos::hash;
int main() {
    // предподсчитываем степени основания хеширования + обратные к ним:
    int n; std::cin >> n;
    std::vector<Hash> powers(n, 1), ipowers(n, 1);
    for (int i = 1; i < n; i++)
        powers[i] = powers[i-1] * base;
    ipowers.back() = powers.back()^(-1);
    for (int i = n-2; i >= 0; i--)
        ipowers[i] = ipowers[i+1] * base;
    auto sorted_powers = powers;
    std::sort(all(sorted_powers));
    // считаем хеш от мультимножества a:
    Hash ha;
    for (int i = 0; i < n-1; i++) {
        int a; std::cin >> a;
        ha += powers[a];
    }
    // читаем дерево и считаем хеши для поддеревьев:
    auto adj = readAdj(n);
    std::vector<Hash> hash(1+n);
    vi depth(1+n);
    std::function<Hash(int,int,int)> calcHash = [&](int u, int p, int d) {
        depth[u] = d;
        for (int v : adj[u]) {
            if (v == p) continue;
            hash[u] += calcHash(v, u, d + 1);
        }
        return hash[u] += powers[d];
    };
    calcHash(1,0,0);
    // находим ответ переподвершиванием:
    Hash rootHash = hash[1];
    vi answer;
    auto getHashForRoot = [&](int u) {
        Hash in = hash[u] * ipowers[depth[u]];
        Hash out = (rootHash - in * base) * base;
        return in + out;
    };
    std::function<void(int,int)> dfs = [&](int u, int p) {
        if (std::binary_search(all(sorted_powers), rootHash - ha))
            answer << u;
        for (int v : adj[u]) {
            if (v == p) continue;
            // как меняется хеш?
            // поддерево приближается, всё остальное отдаляется
            auto SomeVar = AutoRecover(rootHash);
            rootHash = getHashForRoot(v);
            dfs(v,u);
        }
    };
    dfs(1,0);
    // выводим отсортированный ответ:
    std::cout << isz(answer) << '\n';
    std::sort(all(answer));
    for (auto it : answer)
        std::cout << it << ' ';
    std::cout << '\n';
}
