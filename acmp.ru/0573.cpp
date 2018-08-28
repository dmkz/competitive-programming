/*
    Задача: 573. НЛО
    
    Решение: алгоритм Диница, графы, потоки, паросочетания, O(sqrt(n)*n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

#define size(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = (int)1e9+7;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct Node {
    int t, x, y;
    
    static Node read() {
        int h, m, x_, y_;
        scanf("%d:%d %d %d", &h, &m, &x_, &y_);
        return Node{h*60+m,x_,y_};
    }
};

inline bool operator<(const Node& a, const Node& b) {
    return a.t < b.t || (a.t == b.t && (a.x < b.x || (a.x == b.x && a.y < b.y)));
}

bool can_connect(const Node& a, const Node& b, const int speed) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    int dt = b.t - a.t;
    if (dt <= 0) return false;
    // sqrt(dx*dx+dy*dy) / speed <= dt / 60
    return 3600LL * (dx*dx+dy*dy) <= 1LL * dt * dt * speed * speed;
}

struct Graph {
    int n, s, t;
    
    vvi cost, flow;
    
    vi dist, pointer;
    
    Graph(int n_, int s_, int t_) : n(n_), s(s_), t(t_) {
        cost.assign(n, vi(n,0));
        flow.assign(n, vi(n,0));
        dist.assign(n,-1);
        pointer.assign(n,0);
    }
    
    void add_edge(int u, int v, int c) {
        cost[u][v] = c;
    }
    
    bool bfs() {
        dist.assign(n,-1);
        dist[s] = 0;
        std::queue<int> queue;
        queue.push(s);
        while (!queue.empty()) {
            auto u = queue.front(); queue.pop();
            for (int v = 0; v < n; ++v) {
                if (dist[v] == -1 && flow[u][v] < cost[u][v]) {
                    dist[v] = dist[u]+1;
                    queue.push(v);
                }
            }
        }
        return dist[t] != -1;
    }
    
    int dfs(int u, int value) {
        if (!value) return 0;
        if (u == t) return value;
        for (int& v = pointer[u]; v < n; ++v) {
            if (dist[v] != dist[u]+1) continue;
            int pushed = dfs(v,std::min(value, cost[u][v] - flow[u][v]));
            if (pushed) {
                flow[u][v] += pushed;
                flow[v][u] -= pushed;
                return pushed;
            }
        }        
        return 0;
    }

    int dinic() {
        int value = 0, pushed = 0;
        while (bfs()) {
            pointer.assign(n,0);
            while ((pushed = dfs(s,INF))) {
                value += pushed;
            }
        }
        return value;
    }
};

int main() {
    int n, speed;
    scanf("%d %d", &n, &speed);
    std::vector<Node> a;
    for (int i = 0; i < n; ++i) {
        a.push_back(Node::read());
    }
    std::sort(a.begin(), a.end());
    // s = 0
    // first part from 1 to n
    // second part from n+1 to 2*n
    // t = 2*n+1
    Graph G(2*n+2,0,2*n+1);
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (can_connect(a[i],a[j],speed)) {
                G.add_edge(1+i,n+1+j,1);
            }
        }
    }
    for (int i = 1; i <= n; ++i) G.add_edge(0,i,1);
    for (int i = 1; i <= n; ++i) G.add_edge(i+n,2*n+1,1);
    int value = n-G.dinic();
    printf("%d", value);
    return 0;
}