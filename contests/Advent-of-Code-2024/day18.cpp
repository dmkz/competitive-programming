#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void part1() {
    vector<pair<int,int>> cells;
    std::string s;
    while (std::getline(std::cin, s)) {
        int x, y;
        int code = sscanf(s.c_str(), "%d,%d", &x, &y);
        assert(code == 2);
        cells.emplace_back(y, x);
    }
    const int nRows = 71, nCols = 71;
    vector<string> a(nRows, string(nCols, '.'));
    vector visited(nRows * nCols, vector(nRows, vector(nCols, false)));
    for (int t = 0; t < 1024; t++) {
        auto [r,c] = cells[t];
        assert(0 <= r && r < nRows);
        assert(0 <= c && c < nCols);
        a[r][c] = '#';
    }
    visited[0][0][0] = 1;
    int answ{};
    for (int t = 1; ; t++) {
        for (int r = 0; r < nRows; r++)
            for (int c = 0; c < nCols; c++)
                if (a[r][c] == '.') {
                    visited[t][r][c] = (r-1 >= 0 && visited[t-1][r-1][c]) ||
                        (c-1 >= 0 && visited[t-1][r][c-1]) ||
                        (r+1<nRows&& visited[t-1][r+1][c]) ||
                        (c+1<nCols&& visited[t-1][r][c+1]);
                }
        if (visited[t][nRows-1][nCols-1]) {
            answ = t;
            break;
        }
    }
    cout << answ << endl;
}
void part2() {
    vector<pair<int,int>> cells;
    std::string s;
    while (std::getline(std::cin, s)) {
        int x, y;
        int code = sscanf(s.c_str(), "%d,%d", &x, &y);
        assert(code == 2);
        cells.emplace_back(y, x);
    }
    const int nRows = 71, nCols = 71;
    vector<string> a(nRows, string(nCols, '.'));
    // бинарный поиск по номеру первого бита, после которого выход будет перекрыт
    int low = -1, high = isz(cells);
    while (high - low > 1) {
        int mid = (low + high) / 2;
        // проверяем
        // сначала накидываем препятствия на поле
        for (int i = 0; i <= mid; i++) {
            auto [r,c] = cells[i];
            a[r][c] = '#';
        }
        // теперь проверяем достижимость
        vector visited(nRows, vector(nCols, false));
        visited[0][0] = 1;
        queue<pair<int,int>> q;
        q.push({0,0});
        while (q.size()) {
            auto [r, c] = q.front();
            q.pop();
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++)
                    if (dr * dr + dc * dc == 1) {
                        int nr = r + dr, nc = c + dc;
                        if (nr < 0 || nr >= nRows) continue;
                        if (nc < 0 || nc >= nCols) continue;
                        if (a[nr][nc] == '#' || visited[nr][nc])
                            continue;
                        visited[nr][nc] = 1;
                        q.push({nr,nc});
                    }
        }
        // вернуть изменение поля в прежнее состояние:
        for (int i = 0; i <= mid; i++) {
            auto [r,c] = cells[i];
            a[r][c] = '.';
        }
        // обновить границу бинпоиска:
        if (visited[nRows-1][nCols-1])
            low = mid;
        else
            high = mid;
    }
    int answ = high;
    //cout << "high = " << high << endl;
    auto [r,c] = cells[answ];
    cout << c << "," << r << endl;
}
main() {
    part2();
}


