/*
    "Клеверный лист": математическое моделирование
*/

#include <iostream>

typedef long long ll;

int main() {
    ll n, all = 0;
    std::cin >> n;
    while (n--) {
        char t; ll in_l, in_r, out_l, out_r;
        std::cin >> t >> out_l >> out_r >> in_l >> in_r;
        all -= out_l + out_r;
        ll answ = out_l + in_l + all;
        all += in_l + in_r;
        std::cout << (t == 'L' ? -1 : answ) << ' ';
    }
    return 0;
}