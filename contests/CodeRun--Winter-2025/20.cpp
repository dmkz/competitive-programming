#include <bits/stdc++.h>

template<typename T> T getbit(T x, uint32_t i) { return (x >> i) & 1; }
void setmax(auto &x, const auto &y) { if (x < y) x = y; }

struct Node {
    uint32_t xormex{};
    uint32_t nonZeros{};
    uint32_t left{};
    uint32_t right{};
}; // 4 * 4 = 16 байт

// 2 * 200000 * 30 * 16 = 2 * 96 * 10^6 = 2*96 мбайт = 192 мбайта
const uint32_t nodeLimit = 400000 * 30 + 20;
std::vector<Node> trie;

Node &createNewNode(uint32_t &nodeId) {
    nodeId = uint32_t(trie.size());
    assert(nodeId < nodeLimit);
    trie.push_back(Node{});
    assert(nodeId < trie.size());
    return trie[nodeId];
}

Node &getRight(Node &curr) {
    if (curr.right) {
        assert(curr.right < trie.size());
        return trie[curr.right];
    }
    return createNewNode(curr.right);
}

Node &getLeft(Node &curr) {
    if (curr.left) {
        assert(curr.left < trie.size());
        return trie[curr.left];
    }
    return createNewNode(curr.left);
}

void merge(Node &curr, Node &left, Node &right, uint32_t sz) {
    // суммируем количество уникальных элементов:
    curr.nonZeros = std::min(sz, left.nonZeros) + std::min(sz, right.nonZeros);
    // считаем ответ:
    if (curr.nonZeros == 2 * sz)
        curr.xormex = 2 * sz; // полное дерево, есть все элементы
    else {
        curr.xormex = std::max(left.xormex, right.xormex);
        if (left.nonZeros == sz)
            setmax(curr.xormex, sz + right.xormex);
        if (right.nonZeros == sz)
            setmax(curr.xormex, sz + left.xormex);
    }
}

uint32_t insert(Node &curr, uint32_t x, int bit = 29) {
    if (bit < 0) {
        // листовая вершина:
        curr.nonZeros++;
        curr.xormex = 1;
        return 1;
    }
    // рекурсивно вызываемся от поддеревьев:
    uint32_t sz;
    if (getbit(x, bit)) sz = insert(getRight(curr), x, bit-1);
    else sz = insert(getLeft(curr), x, bit-1);
    // мерджим результаты:
    merge(curr, getLeft(curr), getRight(curr), sz);
    return sz * 2;
}

uint32_t remove(Node &curr, uint32_t x, int bit = 29) {
    if (bit < 0) {
        // листовая вершина:
        assert(curr.nonZeros > 0);
        curr.nonZeros--;
        curr.xormex = (curr.nonZeros > 0);
        return 1;
    }
    // рекурсивно вызываемся от поддеревьев:
    uint32_t sz;
    if (getbit(x, bit)) sz = remove(getRight(curr), x, bit-1);
    else sz = remove(getLeft(curr), x, bit-1);
    // мерджим результаты:
    merge(curr, getLeft(curr), getRight(curr), sz);
    return sz * 2;
}

auto fast(auto a, const auto& queries)
{
    // инициализируем двоичный бор:
    trie.clear();
    trie.push_back(Node()); // корень
    for (uint32_t i = 0; i < a.size(); i++)
        insert(trie[0], a[i]);
    // обрабатываем запросы, запоминая ответы:
    std::vector<uint32_t> res = {trie[0].xormex};
    for (const auto &[i, x] : queries) {
        assert(0 <= i && i < a.size());
        remove(trie[0], a[i]);
        insert(trie[0], a[i] = x);
        res.push_back(trie[0].xormex);
    }
    return res;
}

void solve() {
    uint32_t n, q; std::cin >> n >> q;
    std::vector<uint32_t> a(n);
    for (uint32_t i = 0; i < n; i++)
        std::cin >> a[i];
    std::vector<std::pair<uint32_t,uint32_t>> queries;
    while (q --> 0) {
        uint32_t i, x; std::cin >> i >> x;
        i--;
        assert(i < a.size());
        queries.emplace_back(i, x);
    }
    for (auto it : fast(a, queries))
        std::cout << it << '\n';
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    trie.reserve(nodeLimit);
    uint32_t tt; std::cin >> tt;
    while (tt --> 0) solve();
}
