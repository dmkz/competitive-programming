/*
    Задача: 979. Формула 001
    
    Решение: графы, поиск в ширину, геометрия, O(n^2*log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
const int NMAX = 1024;
const int INF = (int)1e9+7;
struct Point {
    int x, y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) { }
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
};
bool operator<(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool operator!=(const Point& a, const Point& b) {
    return a < b || b < a;
}
vi solve (const int s, const int t, const std::vector<Point>& pt) {
    const int n = isz(pt);
    static int dist[NMAX][NMAX], from[NMAX][NMAX];
    std::fill(&dist[0][0], &dist[0][0]+NMAX*NMAX, INF);
    std::fill(&from[0][0], &from[0][0]+NMAX*NMAX,  -1);
    std::vector<Point> sorted;
    for (auto &it : pt) { sorted.push_back(it); }
    std::sort(all(sorted));
    vi index(n);
    for (int i = 0; i < isz(pt); ++i) {
        int j = int(std::lower_bound(all(sorted), pt[i]) - sorted.begin());
        index[j] = i;
    }
    dist[s][s] = 0;
    from[s][s] = s;
    std::queue<int> queue;
    queue.push(s * NMAX + s);
    while (!queue.empty()) {
        const int curr = queue.front() / NMAX;
        const int prev = queue.front() % NMAX;
        queue.pop();
        const int vx = pt[curr].x - pt[prev].x;
        const int vy = pt[curr].y - pt[prev].y;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                Point next_p = pt[curr] + Point(vx+dx,vy+dy);
                auto it = std::lower_bound(all(sorted), next_p);
                if (it == sorted.end() || *it != next_p) {
                    continue;
                }
                const int next = index[int(it - sorted.begin())];
                if (dist[next][curr] > dist[curr][prev] + 1) {
                    dist[next][curr] = dist[curr][prev] + 1;
                    from[next][curr] = curr * NMAX + prev;
                    queue.push(next * NMAX + curr);
                }
            }
        }
    }
    int min = t;
    for (int prev = 0; prev < n; ++prev) {
        if (dist[t][prev] < dist[t][min]) {
            min = prev;
        }
    }
    if (dist[t][min] >= INF) {
        return vi{};
    }
    int state = t * NMAX + min;
    vi answ{t};
    for (int i = dist[t][min]; i > 0; --i) {
        int next = state / NMAX;
        int curr = state % NMAX;
        state = from[next][curr];
        assert(state != -1);
        answ.push_back(curr);
    }
    std::reverse(all(answ));
    return answ;
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        std::vector<Point> pt(n);
        for (auto &it : pt) { std::cin >> it.x >> it.y; }
        vi path = solve(0, n-1, pt);
        if (isz(path) == 0) { std::cout << -1 << "\n"; }
        else {
            std::cout << isz(path)-1 << "\n";
            for (auto it : path) { std::cout << it+1 << ' '; }
            std::cout << std::endl;
        }
    }
    return 0;
}