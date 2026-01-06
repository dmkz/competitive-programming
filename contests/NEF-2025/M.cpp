// динамическое программирование
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
const int inf = (int)1e9+7;
/*
    Для данной строки x вычислим строку y и дальше наша задача сделать
    этот y совпадающим с игреком на входе. Флип в строке x, позиции i
    повлияет на позиции y[i], y[i+1], ..., y[n] - чётность изменится на
    противоположную. Флип в строке y, позиции i, повлияет только на
    символ y[i]. Поэтому решим задачу динамическим программированием.
    Пусть dp[flipped][i] = минимальное количество операций, чтобы
    сделать суффикс i, i+1, i+2, ..., n равным между нашим y и игреком
    во входных данных, при условии, что весь суффикс был "flipped" ранее.
    Тогда каждый раз берём минимум из двух возможных вариантов хода.    
*/
void solve() {
    std::string s, t;
    std::cin >> s >> t;
    for (int i = 0, cnt{}; i < isz(s); i++) {
        cnt += (s[i] - '0');
        s[i] = "01"[cnt % 2];
    }
    // инициализация динамики:
    vvi dp(2, vi(isz(s)+1, inf));
    dp[0][isz(s)] = 0;
    dp[1][isz(s)] = 0;
    // переходы:
    for (int i = isz(s)-1; i >= 0; i--) {
        for (int flipped = 0; flipped < 2; flipped++) {
            char si = flipped ? ('1' - s[i] + '0') : s[i];
            char ti = t[i];
            if (si == ti) {
                // ничего не нужно делать
                setmin(dp[flipped][i], dp[flipped][i+1]);
            } else {
                // мы делаем flip либо в x, либо в y
                // flip в строке y, позиции i:
                setmin(dp[flipped][i], dp[flipped][i+1] + 1);
                // flip в строке x, позиции i:
                setmin(dp[flipped][i], dp[flipped^1][i+1] + 1);
            }
        }
    }
    std::cout << std::min(dp[0][0], dp[1][0] + 1) << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
