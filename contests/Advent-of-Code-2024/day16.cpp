#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
//using namespace std;
using pii = std::pair<int,int>;
const int up = 0, right = 1, down = 2, left = 3;
const int dr[] = {-1,0,+1,0};
const int dc[] = {0,+1,0,-1};

template<typename T>
using PQmin = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using State = std::tuple<int,int,int,int>; // {расстояние, направление, строка, столбец}

void part1() {
    // чтение поля:
    std::string s;
    pii start{-1,-1}, finish{-1,-1};
    std::vector<std::string> a;
    for (int r = 0; std::getline(std::cin, s); r++) {
        for (int c = 0; c < isz(s); c++) {
            // обновляем старт и финиш:
            if (s[c] == 'S')
                start = {r, c};
            else if (s[c] == 'E')
                finish = {r, c};
            // все пустые клетки делаем точками:
            if (s[c] != '#')
                s[c] = '.';
        }
        a.push_back(s);
    }
    const int nRows = isz(a), nCols = isz(a[0]);
    // dist[dir][r][c] = кратчайшее расстояние до клетки (r, c) с направлением dir
    const int inf = (int)1e9+7;
    std::vector dist(4, std::vector(nRows, std::vector(nCols, inf)));
    PQmin<State> pq;
    pq.push({0, right, start.first, start.second});
    while (pq.size()) {
        auto [d, dir, r, c] = pq.top();
        pq.pop();
        if (d >= dist[dir][r][c])
            continue;
        dist[dir][r][c] = d;
        // делаем переходы:
        // 1) перемещение прямо
        int nr = r + dr[dir], nc = c + dc[dir];
        if (a[nr][nc] == '.')
            pq.push({d+1,dir,nr,nc});
        // повороты:
        pq.push({d+1000,(dir+1)%4,r,c});
        pq.push({d+1000,(dir-1+4)%4,r,c});
    }
    // выводим ответ:
    auto [fr, fc] = finish;
    std::cout << std::min({dist[up][fr][fc], dist[right][fr][fc],
                           dist[down][fr][fc], dist[left][fr][fc]}) << std::endl;
}

// алгоритм Дейкстры:
auto dijkstra(const auto &a, pii start, std::vector<int> dirs) {
    const int nRows = isz(a), nCols = isz(a[0]);
    // dist[dir][r][c] = кратчайшее расстояние до клетки (r, c) с направлением dir
    const int inf = (int)1e9+7;
    std::vector dist(4, std::vector(nRows, std::vector(nCols, inf)));
    PQmin<State> pq;
    for (int dir : dirs)
        pq.push({0, dir, start.first, start.second});
    while (pq.size()) {
        auto [d, dir, r, c] = pq.top();
        pq.pop();
        if (d >= dist[dir][r][c])
            continue;
        dist[dir][r][c] = d;
        // делаем переходы:
        // 1) перемещение прямо
        int nr = r + dr[dir], nc = c + dc[dir];
        if (a[nr][nc] == '.')
            pq.push({d+1,dir,nr,nc});
        // повороты:
        pq.push({d+1000,(dir+1)%4,r,c});
        pq.push({d+1000,(dir-1+4)%4,r,c});
    }
    return dist;
}

void part2() {
    // чтение поля:
    std::string s;
    pii start{-1,-1}, finish{-1,-1};
    std::vector<std::string> a;
    for (int r = 0; std::getline(std::cin, s); r++) {
        for (int c = 0; c < isz(s); c++) {
            // обновляем старт и финиш:
            if (s[c] == 'S')
                start = {r, c};
            else if (s[c] == 'E')
                finish = {r, c};
            // все пустые клетки делаем точками:
            if (s[c] != '#')
                s[c] = '.';
        }
        a.push_back(s);
    }
    auto distS = dijkstra(a, start, {right});
    auto distF = dijkstra(a, finish, {up, right, down, left});
    auto [sr, sc] = start;
    auto [fr, fc] = finish;
    const int minDist = std::min({distS[up][fr][fc],   distS[right][fr][fc],
                                  distS[down][fr][fc], distS[left][fr][fc]});
    // будем перебирать все клетки и проверять лежат ли они на кратчайшем пути
    for (int dir = 0; dir < 4; dir++)
        for (int r = 0; r < isz(a); r++)
            for (int c = 0; c < isz(a[0]); c++)
                if (distS[dir][r][c] + distF[(dir+2)%4][r][c] == minDist)
                    a[r][c] = 'O';
    int cntO{};
    for (auto &s : a) {
        for (auto &it : s)
            cntO += (it == 'O');
    }
    std::cout << cntO << std::endl;
}
main() {
    part2();
}

