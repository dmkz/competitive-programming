#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
#define int ll
using namespace std;
const int inf = (int)1e9+7;
const int dr[] = {-1,0,+1,0};
const int dc[] = {0,+1,0,-1};
auto findDistances(int sr, int sc, const auto &a) {
// находит кратчайшие расстояния от клетки (sr,sc) до всех других клеток
    vector dist(a.size(), vector(a[0].size(), inf));
    queue<pair<int,int>> q;
    q.push({sr,sc});
    dist[sr][sc] = 0;
    while (q.size()) {
        auto [r, c] = q.front();
        q.pop();
        if (a[r][c] == '#') // если стена, то никуда не двигаемся
            continue;
        for (int dir = 0; dir < 4; dir++) {
            int nr = r + dr[dir], nc = c + dc[dir];
            if (dist[nr][nc] == inf) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr,nc});
            }
        }
    }
    return dist;
}
void part1() {
    // чтение
    string s;
    vector<string> a;
    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int r = 0; getline(cin, s); r++) {
        a.push_back(s);
        for (int c = 0; c < isz(a[r]); c++)
            if (a[r][c] == 'S') {
                sr = r, sc = c;
                a[r][c] = '.';
            } else if (a[r][c] == 'E') {
                er = r, ec = c;
                a[r][c] = '.';
            }
    }
    assert(sr != -1 && sc != -1 && er != -1 && ec != -1);
    const int nRows = isz(a), nCols = isz(a[0]);
    // предподсчитываем расстояния до всех клеток от S и E:
    auto distS = findDistances(sr,sc,a);
    auto distE = findDistances(er,ec,a);
    const int pathWithout = distS[er][ec];
    // формируем список срезов:
    // стену перебрать + клетку пустую рядом
    int answ{};
    map<int, int> bestCheats;
    for (int r = 1; r + 1 < nRows; r++)
        for (int c = 1; c + 1 < nCols; c++)
            if (a[r][c] == '#') {
                for (int adj = 0; adj < 4; adj++) {
                    int r1 = r + dr[adj], c1 = c + dc[adj];
                    if (a[r1][c1] == '.') {
                        // Нашли срез. Для него надо сравнить путь такой:
                        // S -> (r, c) -> (r1, c1) -> E против S->E
                        // и посмотреть сколько он выиграет
                        int pathWithCheat = distS[r][c] + 1 + distE[r1][c1];
                        int difference = pathWithCheat - pathWithout;
                        bestCheats[difference]++;
                    }
                }
            }
    for (auto &[difference, cnt] : bestCheats) {
        if (difference <= -100)
            answ += cnt;
        if (difference < 0)
            cout << "best[" << difference << "] = " << cnt << endl;
    }
    cout << answ << endl;
}
void part2() {
    // чтение
    string s;
    vector<string> a;
    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int r = 0; getline(cin, s); r++) {
        a.push_back(s);
        for (int c = 0; c < isz(a[r]); c++)
            if (a[r][c] == 'S') {
                sr = r, sc = c;
                a[r][c] = '.';
            } else if (a[r][c] == 'E') {
                er = r, ec = c;
                a[r][c] = '.';
            }
    }
    assert(sr != -1 && sc != -1 && er != -1 && ec != -1);
    const int nRows = isz(a), nCols = isz(a[0]);
    // предподсчитываем расстояния до всех клеток от S и E:
    auto distS = findDistances(sr,sc,a);
    auto distE = findDistances(er,ec,a);
    const int pathWithout = distS[er][ec];
    // формируем список срезов:
    // стену перебрать + клетку пустую рядом
    int answ{};
    map<int, int> bestCheats;
    for (int r = 1; r + 1 < nRows; r++)
        for (int c = 1; c + 1 < nCols; c++)
            if (a[r][c] == '.') {
                for (int r1 = 1; r1 + 1 < nRows; r1++) {
                    for (int c1 = 1; c1 + 1 < nCols; c1++) {
                        int cheatDist = abs(r1-r)+abs(c1-c);
                        if (a[r1][c1] == '.' && cheatDist <= 20) {
                            // Нашли срез. Для него надо сравнить путь такой:
                            // S -> (r, c) -> (r1, c1) -> E против S->E
                            // и посмотреть сколько он выиграет
                            int pathWithCheat = distS[r][c] + cheatDist + distE[r1][c1];
                            int difference = pathWithCheat - pathWithout;
                            bestCheats[difference]++;
                        }
                    }
                }
            }
    for (auto &[difference, cnt] : bestCheats) {
        if (difference <= -100)
            answ += cnt;
        if (difference < 0)
            cout << "best[" << difference << "] = " << cnt << endl;
    }
    cout << answ << endl;
}
main() {
    part2();
}


