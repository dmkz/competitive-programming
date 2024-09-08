#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
void remax(auto &x, const auto &y) { if (x < y) x = y; }
bool getbit(int mask, int i) { return (mask >> i) & 1; }
using vi = std::vector<int>;
using ld = long double;

main() {
    // читаем поле
    std::vector<std::string> a(7);
    for (auto &it : a)
        std::cin >> it;
    // и минимальное кол-во дней и часов которое надо выбрать
    int D, H; std::cin >> D >> H;
    // считаем ответ, перебирая подмножество дней, которое мы возьмём в ответ
    ld answ = 0;
    for (int mask = 1; mask < (1 << 7); mask++) {
        const int d = __builtin_popcount(mask);
        if (D > d)
            continue;
        // для выбранного подмножество дней надо выбрать столбцы с максимальным количеством
        // пустых клеток в этих днях
        vi count(24);
        for (int c = 0; c < 24; c++) {
            for (int r = 0; r < 7; r++) {
                if (getbit(mask, r)) {
                    count[c] += (a[r][c] == '.');
                }
            }
        }
        std::sort(all(count), std::greater<>());
        int p = 0, q = 0;
        for (int h = 1; h < H; h++) {
            q += d;
            p += count[h-1];
        }
        for (int h = H; h <= 24; h++) {
            q += d;
            p += count[h-1];
            remax(answ, p * 1.0L / q);
        }
    }
    std::cout << std::fixed << std::setprecision(12);
    std::cout << answ << std::endl;
}
