#include <bits/stdc++.h>
using tiii = std::tuple<int,int,int>;
int random(int a, int b) {
    static std::mt19937 gen;
    return std::uniform_int_distribution<int>(a, b)(gen);
}
tiii ask(int a, int b, int c) {
    std::cout << "? " << a << " " << b << " " << c << std::endl;
    int res; std::cin >> res;
    if (res == 0) {
        // нет точки внутри => ответ найден
        return std::make_tuple(a, b, c);
    }
    // иначе у нас есть индекс точки, лежащей внутри треугольника
    // он делит наш треугольник на три других
    // давайте выберем рандомный из них и продолжим искать в нём
    if (int t = random(0, 2); t == 0)
        return ask(a, b, res);
    else if (t == 1)
        return ask(a, c, res);
    else
        return ask(b, c, res);
}
void solve() {
    int n; std::cin >> n;
    auto [a, b, c] = ask(1, 2, 3);
    std::cout << "! " << a << " " << b << " " << c << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
