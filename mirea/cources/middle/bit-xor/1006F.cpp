#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using ll = long long;
int n, m;
std::vector<ll> left[24][24], right[24][24];
ll a[24][24];
void get_all_paths(int nSteps, int sr, int sc, int dr0, int dc0, int dr1, int dc1, auto &container) {
    for (int mask = 0; mask < (1 << nSteps); mask++) {
        int r = sr, c = sc, valid = 1; ll res = a[sr][sc];
        for (int bit = 0, nr, nc; valid && bit < nSteps; bit++) {
            // делаем шаг в текущем направлении либо по направлению (dr0,dc0)
            // либо по направлению (dr1, dc1) - в зависимости от того, какой сейчас бит
            if ((mask >> bit) & 1) nr = r + dr1, nc = c + dc1;
            else nr = r + dr0, nc = c + dc0;
            // проверяем не вышли ли за пределы карты
            if (nr > n || nc > m || nr < 1 || nc < 1) valid = 0;
            // если не вышли за пределы, то идём в эту клетку и обновляем ответ
            if (valid) r = nr, c = nc, res ^= a[r][c];
        }
        // в конечном итоге мы пришли в клетку диагонали с результатом res. добавляем его
        if (valid) container[r][c].push_back(res);
    }
    // после того, как прошли все возможные пути, посортим весь контейнер
    for (auto &row : container)
        for (auto &col : row) std::sort(all(col));
}
int main() {
    ll k, answ{0};
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            std::cin >> a[i][j];
    // переберем все пути из (1,1) до каждой клетки диагонали: их <= 2^20
    // и из (n,m) до каждой клетки диагонали: их тоже <= 2^20
    // затем посмотрим, как мы сможем все эти пути скомбинировать, чтобы получить нужный ксор
    const int totalSteps = (n+m-2);
    get_all_paths(totalSteps/2,1,1,1,0,0,1,left);
    get_all_paths((totalSteps+1)/2,n,m,-1,0,0,-1,right);
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= m; c++)
            for (auto li : left[r][c]) {
                auto [x,y] = std::equal_range(all(right[r][c]),k^li^a[r][c]);
                answ += y - x;
            }
    std::cout << answ << std::endl;
    return 0;
}