#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vc = std::vector<char>;
using vvc = std::vector<vc>;
// Сведем задачу к диагоналям, потому что противоположные углы квадрата лежат на одной
// Будет для левого-верхнего угла находить лучший правый-нижний
// Для этого понадобится для левого-верхнего угла посчитать максимальную сторону,
// которую можно достичь: это rightBorder=min(сколько вправо воды, сколько вниз воды)
// А для правого-нижнего угла это leftBorder=min(сколько влево воды, сколько вверх воды)
// Далее можно делать бинпоиск и SparseTable: для каждого левого угла на отрезке [i,rightBorder[i]] находим минимальный суффикс такой, что минимум из leftBorder's на нём лежит левее i
// Но можно, конечно же, без SparseTable обычным сетом или очередью с приоритетами и обработкой событий, но лень

const int PMAX = 13, NMAX = 8*1024;
int min[PMAX][NMAX],sz,leftBorder[NMAX],rightBorder[NMAX];

int getMin(int l, int r) {
    const int len = r - l + 1;
    const int p = std::__lg(len);
    return std::min(min[p][l],min[p][r+1-(1<<p)]);
}
void build() {
    for (int i = 0; i < sz; i++) min[0][i] = leftBorder[i];
    for (int p = 1; p < PMAX; p++) {
        for (int i = 0; i + (1 << p) - 1 < sz; i++) {
            min[p][i] = std::min(min[p-1][i],min[p-1][i+(1<<(p-1))]);
        }
    }
}
void input(int &n, int &m, vvc &map) {
    std::cin >> n >> m;
    map.assign(1+n+1,vc(1+m+1,'.'));
    for (int r = 1; r <= n; r++) {
        std::string s; std::cin >> s;
        assert(isz(s) == m);
        for (int c = 1; c <= m; c++) {
            map[r][c] = s[c-1];
        }
    }
}
int solve(const int n, const int m, const vvc &map) {
    vvi up(1+n+1,vi(1+m+1,0));
    auto down = up, right = up, left = up;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            up[i][j] = (map[i][j] == 'W')*(up[i-1][j]+1);
            left[i][j] = (map[i][j] == 'W')*(left[i][j-1]+1);
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            down[i][j] = (map[i][j] == 'W')*(down[i+1][j]+1);
            right[i][j] = (map[i][j] == 'W')*(right[i][j+1]+1);
        }
    }
    // одна диагональ это i-j==const
    int answ = 0;
    for (int diag = 1-m; diag <= n-1; diag++) {
        // цикл вдоль диагонали: нужно подготовить leftBorder и rightBorder для каждой её клетки:
        sz = 0;
        for (int i = 1; i <= n; i++) {
            const int j = i - diag;
            if (j < 1 || j > m) continue;
            rightBorder[sz] = sz+std::min(right[i][j],down[i][j])-1;
            leftBorder[sz] = sz-std::min(left[i][j],up[i][j])+1;
            sz++;
        }
        // строим SparseTable
        build();
        for (int i = 0; i < sz; i++) {
            const int r = rightBorder[i];
            // находим бинпоиском максимальную сторону квадрата
            // нужно найти суффикс минимальной длины на отрезке [i, r] такой, что
            // минимум на нем <= i
            int low = i-1, high = r+1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (getMin(mid,r) <= i) low = mid;
                else high = mid;
            }
            answ = std::max(answ,low-i+1);
        }
    }
    return answ * answ;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n,m;
    vvc map;
    input(n,m,map);
    std::cout << solve(n,m,map) << std::endl;
}