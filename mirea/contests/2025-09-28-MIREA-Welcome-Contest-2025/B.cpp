#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void solve() {
    int n, k; std::cin >> n >> k;
    std::string s; std::cin >> s;
    if (k < n) {
        // если длина строки меньше, чем лимит, то добавим букву A в конец
        s += 'A';
    } else {
        // иначе добавлять буквы нельзя, поэтому удаляем все буквы X с конца
        // и последнюю букву A заменяем на X (пример: AXXXX -> X)
        std::string t = s;
        while (isz(t) && t.back() == 'X')
            t.pop_back();
        if (isz(t)) {
            assert(t.back() == 'A');
            t.back() = 'X';
            s = t;
        }
    }
    std::cout << s << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
