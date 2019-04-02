/*
    Задача: 616. Отношения
    
    Решение: конструктив, жадный алгоритм, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
typedef std::vector<std::string> vs;
typedef std::vector<int> vi;
bool solve(const int n, const vs& arr, vi& f, vi& g) {
    vi x(n), y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = x[i] = i;
    }
    vi nx1(n), ny0(n);
    for (int i : x) {
        for (int j : y) {
            nx1[i] += (arr[i][j] == '1');
            ny0[j] += (arr[i][j] == '0');
        }
    }
    int curr = 0;
    while (isz(x) > 0 || isz(y) > 0) {
        int candX = -1, candY = -1;
        for (int i : x) {
            if (nx1[i] == isz(y)) {
                candX = i;
                break;
            }
        }
        for (int j : y) {
            if (ny0[j] == isz(x)) {
                candY = j;
                break;
            }
        }
        if (candX == -1 && candY == -1) {
            return false;
        }
        if (candX != -1) {
            f[candX] = curr++;
            x.erase(std::find(all(x), candX));
            for (int j : y) {
                ny0[j] -= (arr[candX][j] == '0');
            }
        }
        if (candY != -1) {
            g[candY] = curr++;
            y.erase(std::find(all(y), candY));
            for (int i : x) {
                nx1[i] -= (arr[i][candY] == '1');
            }
        }
    }
    return true;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        vs arr(n); for (auto &it : arr) { std::cin >> it; }
        vi f(n), g(n);
        bool flag = solve(n, arr, f, g);
        if (flag) {
            std::cout << "YES\n";
            for (auto it : f) { std::cout << it << ' '; }
            std::cout << "\n";
            for (auto it : g) { std::cout << it << ' '; }
            std::cout << "\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}