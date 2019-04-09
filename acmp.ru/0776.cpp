/*
    Задача: 776. Юпитер
    
    Решение: графы, поиск в ширину, O(k*n*m*(n+m))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef const int cint;
template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
    for (auto &it : vec) { is >> it; }
    return is;
}
const int INF = (int)1e9+7;
struct Pos { int k, r, c; };

int solve(cint tr, cint tc, cint nRows, cint nCols, cint k, cint d, const vvi& h) {
    vvvi dist(1+k, vvi(nRows, vi(nCols, INF)));
    dist[k][0][0] = 0;
    std::queue<Pos> queue;
    queue.push(Pos{k,0,0});
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        const int r = curr.r;
        const int c = curr.c;
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr * dr + dc * dc != 1) { continue; }
                int nr = curr.r + dr;
                int nc = curr.c + dc;
                if (nr < 0 || nr >= nRows || nc < 0 || nc >= nCols) {
                    continue;
                }
                const int newDist = dist[curr.k][r][c] + 1;
                if (h[nr][nc] > 0 && std::abs(h[r][c] - h[nr][nc]) <= 1 && dist[curr.k][nr][nc] == INF) {
                    dist[curr.k][nr][nc] = newDist;
                    queue.push(Pos{curr.k,nr,nc});
                }
                if (curr.k == 0) { continue; }
                int max = h[r][c];
                while (!(nr < 0 || nr >= nRows || nc < 0 || nc >= nCols)) {
                    max = std::max(max, h[nr][nc]);
                    int need = max - h[r][c] + max - h[nr][nc] + std::abs(nr - r) + std::abs(nc - c);
                    if (need <= d && h[nr][nc] > 0 && dist[curr.k-1][nr][nc] == INF) {
                        dist[curr.k-1][nr][nc] = newDist;
                        queue.push(Pos{curr.k-1,nr,nc});
                    }
                    nr += dr;
                    nc += dc;
                }
            }
        }
    }
    int min = INF;
    for (int i = 0; i <= k; ++i) { min = std::min(min, dist[i][tr][tc]); }
    return min;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int nCols, nRows;
    while (std::cin >> nCols >> nRows) {
        int tc, tr, k, d; std::cin >> tc >> tr; --tc,--tr;
        vvi h(nRows, vi(nCols)); std::cin >> k >> d >> h;
        int ans = solve(tr, tc, nRows, nCols, k, d, h);
        std::cout << (ans == INF ? "IMPOSSIBLE" : std::to_string(ans)) << std::endl;
    }
    return 0;
}