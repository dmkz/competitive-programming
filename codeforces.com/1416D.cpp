/*
    Problem: 1416D. Graph and Queries
    Solution: graphs, dsu, segment tree, queries offline, O(n*log(n))
*/
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using li = std::list<int>;
using vi = std::vector<int>;
using vli = std::vector<li>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;


struct DSUList {
    vi par;
    vli data;
    DSUList(int n) : par(n,0),data(n,{0}) {
        for (int i = 0; i < n; i++) par[i] = i, data[i] = {i};
    }
    int getParent(int u) {
        return par[u] == u ? u : par[u] = getParent(par[u]);
    }
    void connect(int u, int v) {
        u = getParent(u);
        v = getParent(v);
        if (u == v) return;
        if (isz(data[u]) <= isz(data[v])) {
            data[v].insert(data[v].begin(),all(data[u]));
            par[u] = v;
            data[u].clear();
        } else {
            data[u].insert(data[u].end(),all(data[v]));
            par[v] = u;
            data[v].clear();
        }
    }
};
struct DSUSegs {
    vi par,start,end,sz;
    DSUSegs(int n) : par(n,0),start(n,0),end(n,0),sz(n,1) {
        for (int i = 0; i < n; i++) par[i] = i;
        // надеюсь кто-нибудь проинициализирует start извне
    }
    int getParent(int u) {
        return par[u] == u ? u : par[u] = getParent(par[u]);
    }
    int connect(int u, int v) {
        u = getParent(u);
        v = getParent(v);
        if (u == v) return isz(par);
        int lu = start[u];
        int ru = end[u];
        int lv = start[v];
        int rv = end[v];
        assert(ru == lv || rv == lu);
        if (sz[u] < sz[v]) std::swap(u,v);
        assert(sz[u] >= sz[v]);
        par[v] = u;
        sz[u] += sz[v];
        int delim = std::max(lu,lv);
        start[u] = std::min(lu,lv);
        end[u] = std::max(ru,rv);
        return delim;
    }
};
pii merge(pii a, pii b) {
    if (a.first >= b.first) return a;
    else return b;
}
struct SegTree {
    vpii data;
    SegTree(const vi& arr) : data(4 * isz(arr), pii{-1,-1}) { build(0,0,isz(arr),arr); }
    void build(int v, int l, int r, const vi& arr) {
        if (l + 1 == r) {
            data[v] = {arr[l],l};
        } else {
            int m = (l + r) / 2;
            build(2*v+1,l,m,arr);
            build(2*v+2,m,r,arr);
            data[v] = merge(data[2*v+1], data[2*v+2]);
        }
    }
    pii get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return pii(-1,-1);
        if (ql <= l && r <= qr) return data[v];
        int m = (l+r)/2;
        return merge(get(2*v+1,l,m,ql,qr),get(2*v+2,m,r,ql,qr));
    }
    void set(int v, int l, int r, int p, int x) {
        if (p < l || p >= r) return;
        if (l + 1 == r) {
            data[v] = {x,p};
        } else {
            int m = (l+r)/2;
            set(2*v+1,l,m,p,x);
            set(2*v+2,m,r,p,x);
            data[v] = merge(data[2*v+1], data[2*v+2]);
        }
    }
};

vi solve(const int nV, const int nE, const int nQ, vi number, vpii edges, vpii queries) {
    assert(nQ == isz(queries));
    vi willBeRemoved(nE);
    for (auto &[fi,se] : queries) {
        if (fi == 2) willBeRemoved[se] = 1;
    }
    for (int i = 0; i < nE; i++) {
        if (!willBeRemoved[i]) queries.emplace_back(2,i);
    }
    // надо найти порядок вершин который позволит при удалении ребра разбивать компоненту
    // на два непрерывных отрезка
    std::reverse(all(queries));
    DSUList dsuList(nV);
    for (auto &[fi,se] : queries) {
        if (fi == 2) {
            auto &[u,v] = edges[se];
            dsuList.connect(u,v);
        }
    }
    // вроде dsu все соединило в нужном порядке, сливаем компоненты в массив
    std::set<int> start{nV};
    vi order;
    for (int u = 0; u < nV; u++) {
        int p = dsuList.getParent(u);
        start.insert(isz(order));
        order.insert(order.end(), all(dsuList.data[p]));
        dsuList.data[p].clear();
    }
    assert(isz(order) == nV);
    vi pos(nV);
    for (int i = 0; i < nV; i++) pos[order[i]] = i;
    // вроде готово
    // надо понять как запросы будут делить непрерывные отрезки на две части
    DSUSegs dsuSegs(nV);
    for (int u = 0; u < nV; u++) {
        dsuSegs.start[u] = pos[u];
        dsuSegs.end[u] = pos[u]+1;
    }
    vi delimiters;
    for (auto &[fi,se] : queries) {
        if (fi == 2) {
            auto &[u,v] = edges[se];
            int mid = dsuSegs.connect(u,v);
            delimiters.push_back(mid);
        }
    }
    // готовы отвечать на запросы
    std::reverse(all(queries));
    vi arr(nV);
    for (int u = 0; u < nV; u++) arr[pos[u]] = number[u];
    SegTree st(arr);
    vi answer;
    for (auto &[fi,se] : queries) {
        if (fi == 1) {
            int u = se;
            auto r = start.upper_bound(pos[u]);
            assert(r != start.begin());
            auto l = std::prev(r);
            pii answ = st.get(0,0,nV,*l,*r);
            answer.push_back(answ.first);
            st.set(0,0,nV,answ.second,0);
        } else {
            start.insert(delimiters.back());
            delimiters.pop_back();
        }
    }
    return answer;
}

using std::cin;
using std::cout;

void readTest(int &nV, int &nE, int &nQ, vi& number, vpii& edges, vpii& queries) {
    cin >> nV >> nE >> nQ;
    number.resize(nV); for (auto & it : number) cin >> it;
    edges.resize(nE);
    for (auto &[u,v]: edges) cin >> u >> v,u--,v--;
    queries.resize(nQ);
    for (auto &[fi,se] : queries) {
        cin >> fi >> se;
        se--;
    }
    // наконец-то прочитали все данные!
}

int main() {
    int nV,nE,nQ;
    vi number;
    vpii edges, queries;
    readTest(nV,nE,nQ,number,edges,queries);
    auto answ = solve(nV,nE,nQ,number,edges,queries);
    for (auto it : answ) cout << it << '\n';
    return 0;
}