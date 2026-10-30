#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using pii = pair<int,int>;
// храним таблицу игры: побеждает ли человек, который ходит в этой ситуации, и каким конкретно ходом
pair<int,int> table[201][201];
const pii lose = {0,0};
void precalc() {
    // исследуем всю таблицу игры до начала запросов:
    table[0][0] = lose;
    for (int sum = 1; sum <= 400; sum++)
        for (int a = 0; a <= 200; a++)
            if (int b = sum - a; 0 <= b && b <= 200) {
                pii step = lose;
                // исследуем состояние (a, b): нужно найти такой ход, который ставит соперника в проигрыш
                // ход 1. берём с первой тарелки
                for (int x = 1; x <= a; x++)
                    if (table[a-x][b] == lose) {
                        step = {x, 0};
                        break;
                    }
                // ход 2. берём со второй тарелки
                for (int x = 1; x <= b; x++)
                    if (table[a][b-x] == lose) {
                        step = {0, x};
                        break;
                    }
                // ход 3. берём сразу с обеих тарелок
                for (int x = 1; x * x <= std::min(a, b); x++)
                    if (int xx = x*x; table[a-xx][b-xx] == lose) {
                        step = {xx, xx};
                        break;
                    }
                table[a][b] = step;
            }
}
void solve() {
    // начинаем играть
    int a, b; cin >> a >> b;
    if (table[a][b] == lose) {
        cout << "Second" << endl;
    } else {
        cout << "First" << endl;
        auto [x,y] = table[a][b];
        cout << x << ' ' << y << endl;
        a -= x, b -= y;
    }
    while (a+b>0) {
        // ход жюри:
        int x, y; cin >> x >> y;
        a -= x, b -= y;
        // наш ход:
        tie(x,y) = table[a][b];
        cout << x << ' ' << y << endl;
        a -= x, b -= y;
    }
}
int32_t main() {
    precalc();
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}