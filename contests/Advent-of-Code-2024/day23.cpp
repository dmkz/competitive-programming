#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using pii = std::pair<int,int>;
int lowpos(const auto &v, const auto &x) {
// возвращает индекс элемента x в векторе v
    return int(std::lower_bound(all(v), x) - v.begin());
}

void setmax(auto &x, const auto &y) { if (x < y) x = y; }


void part1(const auto & edges, const auto & vertices) {
    std::vector adj(isz(vertices), std::vector<int>{});
    for (const auto &[u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int answ[4]{};
    for (int a = 0; a < isz(vertices); a++)
        if (vertices[a][0] == 't') {
            for (int i = 0; i < isz(adj[a]); i++)
                for (int j = i+1; j < isz(adj[a]); j++) {
                    int b = adj[a][i], c = adj[a][j];
                    if (b > c) std::swap(b, c);
                    bool isTInB = (vertices[b][0] == 't');
                    bool isTInC = (vertices[c][0] == 't');
                    if (std::binary_search(all(edges), pii(b,c)))
                        answ[1+isTInB+isTInC]++;
                }
        }
    std::cout << "part1 = ";
    std::cout << (answ[1] + answ[2] / 2 + answ[3] / 3) << std::endl;
}

void part2(const auto & edges, const auto & vertices) {
    const int nVert = isz(vertices);
    std::vector adj(nVert, std::vector<int>{});
    for (const auto &[u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    std::vector<int> answ;
    for (int i = 0; i < nVert; i++) {
        // мы включим в множество текущую вершину и подмножество её соседей
        // всего подмножеств в худшем случае 2^13
        // переберём их все и проверим что каждая вершина подмножества
        // связана с каждой другой вершиной подмножества
        for (int mask = 0; mask < (1 << isz(adj[i])); mask++) {
            // конвертируем битмаску в множество вершин
            std::vector<int> subset{i};
            for (int j = 0; j < isz(adj[i]); j++)
                if ((mask >> j) & 1)
                    subset.push_back(adj[i][j]);
            // перебираем все пары вершин подмножества и проверим что они связаны
            bool ok = 1;
            for (int ia = 0; ok && ia < isz(subset); ia++)
                for (int ib = ia+1; ok && ib < isz(subset); ib++) {
                    int a = subset[ia], b = subset[ib];
                    if (a > b) std::swap(a, b);
                    ok &= (std::binary_search(all(edges), pii(a,b)));
                }
            if (ok && isz(answ) < isz(subset))
                answ = subset;
        }
    }
    // выводим ответ
    std::set<std::string> answer;
    for (int i : answ)
        answer.insert(vertices[i]);
    std::string output;
    for (const auto &it : answer)
        (output += it) += ',';
    assert(isz(output));
    output.pop_back();
    std::cout << "part2 = '" << output << "'" << std::endl;
}

main() {
    std::vector<pii> edges;
    std::vector<std::string> vertices;
    {
        // читаем рёбра в виде строка-строка, затем пронумеруем все строки
        // целыми неотрицательными числами и сделаем рёбра число-число,
        // запоминая отдельно, какому числу какая строка соответствует
        std::vector<std::pair<std::string,std::string>> sedges;
        std::string s;
        while (std::getline(std::cin, s)) {
            auto u = s.substr(0, 2);
            auto v = s.substr(3, 2);
            sedges.emplace_back(u, v);
            vertices.push_back(u);
            vertices.push_back(v);
        }
        std::sort(all(vertices));
        vertices.erase(std::unique(all(vertices)), vertices.end());
        for (const auto &[su, sv] : sedges)
            edges.emplace_back(lowpos(vertices, su), lowpos(vertices, sv));
        for (auto &[u, v] : edges)
            if (u > v) std::swap(u, v);
        std::sort(all(edges));
    }
    //part1(edges, vertices);
    part2(edges, vertices);
}
