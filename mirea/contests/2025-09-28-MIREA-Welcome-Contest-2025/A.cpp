#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void solve() {
    // посчитаем количество имён и фамилий, длина которых
    // совпадает с количеством вопросительных знаков в шаблонах
    // и перемножим эти числа
    std::string a, b;
    std::cin >> a >> b;
    int n, m; std::cin >> n >> m;
    int cntN{}, cntM{};
    for (int i = 0; i < n; i++) {
        std::string s; std::cin >> s;
        cntN += (isz(a) == isz(s));
    }
    for (int i = 0; i < m; i++) {
        std::string s; std::cin >> s;
        cntM += (isz(b) == isz(s));
    }
    std::cout << cntN * cntM << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
