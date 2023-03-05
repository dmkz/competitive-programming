/*
Решение сгенерировано с помощью ChatGPT
    
Описание решения от самой ChatGPT:
    Здесь используется структура Point для представления клетки
    на шахматной доске. Функция check проверяет, может ли черный
    конь сделать ход из клетки a в клетку b. Функция bfs реализует
    алгоритм поиска в ширину для поиска кратчайшего пути от черного
    коня до белого коня. Если такой путь существует и его длина
    меньше или равна 10000000, то ответом является YES, иначе NO.
*/
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 3005;
int n, m, rw, cw, rb, cb;
bool vis[MAXN][MAXN];

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

bool check(Point a, Point b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    return dx == 2 && dy == 1 || dx == 1 && dy == 2;
}

int bfs(Point start, Point end) {
    queue<pair<Point, int>> q;
    q.push({start, 0});
    memset(vis, false, sizeof(vis));
    vis[start.x][start.y] = true;

    while (!q.empty()) {
        Point cur = q.front().first;
        int step = q.front().second;
        q.pop();

        if (cur.x == end.x && cur.y == end.y) {
            return step;
        }

        for (int dx = -2; dx <= 2; ++dx) {
            for (int dy = -2; dy <= 2; ++dy) {
                if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) continue;
                Point nxt(cur.x + dx, cur.y + dy);
                if (nxt.x < 1 || nxt.x > n || nxt.y < 1 || nxt.y > m) continue;
                if (vis[nxt.x][nxt.y]) continue;
                if (check(nxt, end)) {
                    return step + 1;
                }
                q.push({nxt, step + 1});
                vis[nxt.x][nxt.y] = true;
            }
        }
    }

    return -1;
}

int main() {
    cin >> n >> m >> rw >> cw >> rb >> cb;
    Point white(rw, cw), black(rb, cb);
    int steps = bfs(black, white);
    if (steps != -1 && steps <= 10000000) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}