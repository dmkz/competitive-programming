#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void trim(string &s) {
    for (int rot = 0; rot < 2; rot++) {
        while (isz(s) && isspace(s.back()))
            s.pop_back();
        reverse(all(s));
    }
}
void part1() {
    int64_t answ{};
    string s;
    // читаем правила
    map<int, set<int>> prev;
    while (getline(cin, s)) {
        trim(s);
        if (s.empty())
            break;
        int before, after;
        int code = sscanf(s.c_str(), "%d|%d", &before, &after);
        assert(code == 2);
        prev[after].insert(before);
    }
    // читаем списки
    while (getline(cin, s)) {
        trim(s);
        s += ',';
        // конвертим строчку в вектор чисел
        vector<int> a;
        while (s.size()) {
            int p = (int)s.find(',');
            assert(p != -1);
            int x;
            int code = sscanf(s.c_str(), "%d", &x);
            assert(code == 1);
            a.push_back(x);
            s = s.substr(p+1);
        }
        // обрабатываем вектор
        bool ok = true;
        for (int i = 0; i + 1 < isz(a); i++)
            for (int j = i + 1; j < isz(a); j++) {
                // порядок: сначала a[i], потом a[j]
                // если это нарушает какое-то правило, то false
                int cnt = (int)prev[a[i]].count(a[j]);
                ok &= (cnt == 0);
            }
        if (ok) {
            assert(isz(a) % 2 == 1);
            answ += a[isz(a) / 2];
        }
    }
    cout << answ << endl;
}

// топологический порядок
struct Graph {
    
    int n;
    
    vector<vector<int>> next;
    
    vector<vector<int>> adj;
    
    vector<int> priority, visited, comp, order;
    
    vector<vector<int>> compElements;
    
    
    Graph(int n_)
        : n(n_), next(1+n), adj(1+n)
        , priority(1+n), visited(1+n, false), comp(1+n, 0)
    { }
    
    void addEdge(int u, int v) {
        next[u].push_back(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void findComponents() {
        int nComp = 0;
        compElements.assign(1, vector<int>{});
        for (int u = 1; u <= n; u++)
            if (!comp[u]) {
                int compId = ++nComp;
                vector<int> q = {u};
                for (int i = 0; i < isz(q); i++)
                    for (int v : adj[q[i]])
                        if (!comp[v]) {
                            comp[v] = compId;
                            q.push_back(v);
                        }
                compElements.push_back(q);
            }
    }
    
    void topsort(int u) {
        if (visited[u]) return;
        visited[u] = 1;
        for (int v : next[u]) topsort(v);
        order.push_back(u);
    }
    
    void build() {
        for (int u = 1; u <= n; u++)
            topsort(u);
        reverse(all(order));
        for (int i = 0; i < isz(order); i++)
            priority[order[i]] = i;
    }
    
    auto getCompare() {
        return [this](int lhs, int rhs){
            return priority[lhs] < priority[rhs];
        };
    }
    
    bool isSorted(const vector<int> &a) {
        return is_sorted(all(a), getCompare());
    }
    
    void sort(vector<int> &a) {
        std::sort(all(a), getCompare());
    }
    
};

void part1Modified() {
    int64_t answ{};
    string s;
    // читаем правила
    vector<pair<int,int>> edges;
    while (getline(cin, s)) {
        trim(s);
        if (s.empty())
            break;
        int before, after;
        int code = sscanf(s.c_str(), "%d|%d", &before, &after);
        assert(code == 2);
        edges.emplace_back(before, after);
    }
    // читаем списки
    while (getline(cin, s)) {
        trim(s);
        s += ',';
        // конвертим строчку в вектор чисел
        vector<int> a;
        while (s.size()) {
            int p = (int)s.find(',');
            assert(p != -1);
            int x;
            int code = sscanf(s.c_str(), "%d", &x);
            assert(code == 1);
            a.push_back(x);
            s = s.substr(p+1);
        }
        vector<int> b = a;
        sort(all(b));
        Graph g(99);
        for (auto [u, v] : edges) {
            if (binary_search(all(b), u) && binary_search(all(b), v)) {
                g.addEdge(u, v);
            }
        }
        g.findComponents();
        g.build();
        map<int, vector<int>> elements;
        for (int x : a)
            elements[g.comp[x]].push_back(x);
        bool ok = 1;
        for (const auto &[_, items] : elements)
            ok &= g.isSorted(items);
        if (ok) {
            assert(isz(a) % 2 == 1);
            answ += a[isz(a)/2];
        }
    }
    cout << answ << endl;
}

void part2() {
    int64_t answ{};
    string s;
    // читаем правила
    vector<pair<int,int>> edges;
    while (getline(cin, s)) {
        trim(s);
        if (s.empty())
            break;
        int before, after;
        int code = sscanf(s.c_str(), "%d|%d", &before, &after);
        assert(code == 2);
        edges.emplace_back(before, after);
    }
    // читаем списки
    while (getline(cin, s)) {
        trim(s);
        s += ',';
        // конвертим строчку в вектор чисел
        vector<int> a;
        while (s.size()) {
            int p = (int)s.find(',');
            assert(p != -1);
            int x;
            int code = sscanf(s.c_str(), "%d", &x);
            assert(code == 1);
            a.push_back(x);
            s = s.substr(p+1);
        }
        vector<int> b = a;
        sort(all(b));
        Graph g(99);
        for (auto [u, v] : edges) {
            if (binary_search(all(b), u) && binary_search(all(b), v)) {
                g.addEdge(u, v);
            }
        }
        g.findComponents();
        g.build();
        map<int, vector<int>> elements;
        for (int x : a)
            elements[g.comp[x]].push_back(x);
        bool ok = 1;
        for (const auto &[_, items] : elements)
            ok &= g.isSorted(items);
        if (!ok) {
            assert(isz(a) % 2 == 1);
            assert(elements.size() == 1);
            g.sort(a);
            answ += a[isz(a)/2];
        }
    }
    cout << answ << endl;
}
main() {
    part2();
}
