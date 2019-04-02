/*
    Задача: 915. Кубик - 2
    
    Решение: динамическое программирование, двумерное дп, O(n*m)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
const int INF = (int)1e9+7;
template<typename T> std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
    for (auto &it : vec) { is >> it; }
    return is;
}
template<typename T1, typename T2>
T1& remax(T1& a, const T2& b) {
    return a = (a >= b ? a : b);
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);    
    int n, m; std::cin >> n >> m;
    vvi a(n, vi(m));
    std::cin >> a;
    vvvi max(7, vvi(n, vi(m, -INF)));
    for (int side = 1; side <= 6; ++side) {
        max[side][0][0] = a[0][0] * side;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int curr = 1; curr <= 6; ++curr) {
                for (int next = 1; next <= 6; ++next) {
                    if (j+1 < m && next != curr && next + curr != 7) {
                        remax(max[next][i][j+1], a[i][j+1] * next + max[curr][i][j]);
                    }
                    if (i+1 < n && next != curr && next + curr != 7) {
                        remax(max[next][i+1][j], a[i+1][j] * next + max[curr][i][j]);
                    }
                }
            }
        }
    }
    int res = -INF;
    for (int s = 1; s <= 6; ++s) {
        remax(res, max[s].back().back());
    }
    std::cout << res << std::endl;
    return 0;
}