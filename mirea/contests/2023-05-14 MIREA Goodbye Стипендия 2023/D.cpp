#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using vs = vector<string>;
using ll = long long;
using pii = pair<int,int>;
using vvpii = vector<vector<pii>>;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; ll t; std::cin >> n >> t;
        vs a(2*n+1);
        for (auto &row : a)
            std::cin >> row;
        // создаём паровозики
        vvpii trains(n+1);
        const int centerRow = n, centerCol = n;
        for (int i = 0; i <= n; i++) {
            auto &tr = trains[i];
            {   // начиная с левого верхнего угла, прошаем вдоль сторон и
                // сложим весь пройденный путь в вектор из пар
                int r = centerRow - i, c = centerCol - i;
                tr.emplace_back(r,c);
                // шагаем слева-направо по верхней стороне:
                while (c < centerCol + i) tr.emplace_back(r,++c);
                // шагаем сверху-внизу по правой стороне:
                while (r < centerRow + i) tr.emplace_back(++r,c);
                // шагаем справа-налево по нижней стороне:
                while (c > centerCol - i) tr.emplace_back(r,--c);
                // шагаем сверху-вниз по левой стороне:
                while (r > centerRow - i + 1) tr.emplace_back(--r,c);
            }
            // теперь находим пустую клетку на текущем пути
            int emptyPos = 0;
            while (emptyPos < isz(tr)) {
                auto [r,c] = tr[emptyPos];
                if (a[r][c] == '.') {
                    a[r][c] = '#';
                    break;
                }
                emptyPos++;
            }
            assert(emptyPos != isz(tr));
            // так как мы движемся по циклу, то можем посчитать,
            // где окажемся через t шагов, взяв остаток от деления на длину цикла:
            emptyPos = (emptyPos + t) % isz(tr);
            // ставим пустую клетку:
            auto [r,c] = tr[emptyPos];
            a[r][c] = '.';
        }
        // выводим ответ:
        std::cout << std::string(2*n+1,'-') << '\n';
        for (auto &s : a) std::cout << s << '\n';
    }
    return 0;
}