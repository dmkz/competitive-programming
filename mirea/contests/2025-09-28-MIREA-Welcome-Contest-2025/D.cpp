#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void solve() {
    // читаем строку и для каждой буквы (26 букв всего) посчитаем
    // её количество на каждом префиксе (префикс-суммы)
    // тогда сможем для каждой буквы говорить, сколько её на отрезке от L до R
    // за O(1): prefSum[R+1][буква] - prefSum[L][буква]
    std::string s; std::cin >> s;
    std::vector<std::array<int, 26>> cnt(isz(s)+1);
    for (int i = 0; i < isz(s); i++) {
        cnt[i+1] = cnt[i];
        if (s[i] != '?')
            cnt[i+1][s[i] - 'a']++;
    }
    // функция для нахождения количества букв "x" на отрезке [l, r]:
    auto findCountEqual = [&](int l, int r, char x) {
        return cnt[r+1][x-'a'] - cnt[l][x-'a'];
    };
    int q; std::cin >> q;
    while (q --> 0) {
        int l, r; char x; std::cin >> l >> r >> x;
        l--, r--;
        // количество равных "x":
        int cntEqual = findCountEqual(l, r, x);
        // количество меньших "x":
        int cntLess = 0;
        for (char c = 'a'; c < x; c++)
            cntLess += findCountEqual(l, r, c);
        // количество больщих "x":
        int cntGreater = 0;
        for (char c = x+1; c <= 'z'; c++)
            cntGreater += findCountEqual(l, r, c);
        // количество знаков вопроса:
        int cntQuestions = (r-l+1) - cntLess - cntEqual - cntGreater;
        // если нет символа x и нет вопросиков, то ответ 0 0
        if (cntEqual == 0 && cntQuestions == 0) {
            std::cout << "0 0\n";
        } else {
            // иначе заменяем все вопросы буквами "x"
            // тогда наш отрезок в отсортированном виде будет выглядеть:
            // [меньшие буквы] [буквы "x"] [большие буквы]
            // лучше нельзя: если мы будем заменять некоторые вопросы буквами,
            // меньшими чем "x", то правая граница отрезка двигаться не будет:
            // [меньшие буквы ---->] ["x"] [большие буквы]
            // иначе, если мы будем заменять некоторые вопросы буквами,
            // большими чем "x", то левая граница отрезка из "x" двигаться не будет:
            // [меньшие буквы] ["x"] [<---- большие буквы]
            cntEqual += cntQuestions;
            std::cout << cntLess + 1 << ' ' << cntLess + cntEqual << '\n';
        }
    }
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
