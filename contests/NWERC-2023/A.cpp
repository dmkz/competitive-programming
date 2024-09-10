#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define int ll
void remax(auto &x, const auto &y) { if (x < y) x = y; }
using ll = long long;
/*
    Решим при помощи бинарного поиска + префикс сумм
    Перебираем i2, сколько розеток с остатком равным 2 мы выставляем - O(n) вариантов
    Для каждого варианта найдём бинарным поиском сколько розеток остатка 0 и 1
    мы выставим к ним. Допустим, зафиксировали в бин.поиске, сколько 1 выставим
    Пусть это количество равно i1
    Тогда остатки 2 и остатки 1 соединяем: min(i2, i1)
    Оставшиеся остатки 1 соединяем между собой: (i1 - i2) / 2
    Если "сумма - min(i2, i1) - max(0, (i1 - i2)) / 2 <= s", то можем столько выставить,
    иначе нет
*/
int solve(std::vector<int> w, int s) {
    assert(std::is_sorted(all(w)));
    // распределяем числа по остаткам от деления на 3:
    std::vector<std::pair<int, int>> rem01;
    std::vector<int> rem2;
    for (auto it : w) {
        if (it % 3 == 2) {
            rem2.push_back((it+1)/3);
        } else {
            rem01.emplace_back((it+2)/3, -it % 3);
        }
    }
    std::sort(all(rem01));
    // считаем префикс суммы:
    std::vector<int> prefSum{0}, prefCnt1{0};
    for (auto [val, rem] : rem01) {
        prefSum.push_back(prefSum.back()+val);
        prefCnt1.push_back(prefCnt1.back()-rem);
    }
    // переберём сколько чисел остатка 2 мы берём:
    int sum2 = 0, answ = 0;
    for (int i2 = 0; i2 <= isz(rem2); i2++) {
        // теперь мы сделаем бинарный поиск по тому, сколько ещё можем взять
        int low = -1, high = isz(rem01)+1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            // что будет если мы возьмём "mid" дополнительных розеток?
            int sum = prefSum[mid] + sum2;
            int cnt1 = prefCnt1[mid];
            // остатки 1 мы сочетаем с остатками 2:
            sum -= std::min(i2, cnt1);
            cnt1 -= i2;
            // оставшиеся остатки 1 мы можем между собой соединить:
            if (cnt1 > 0)
                sum -= cnt1 / 2;
            // проверка условия бинпоиска:
            if (sum <= s)
                low = mid;
            else
                high = mid;
        }
        if (low >= 0)
            remax(answ, low+i2);
        if (i2 < isz(rem2))
            sum2 += rem2[i2];
    }
    return answ;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, s; std::cin >> n >> s;
    std::vector<int> w(n);
    for (auto &it : w)
        std::cin >> it;
    // крайние случаи:
    if (s == 1) {
        std::cout << "1\n";
        return 0;
    }
    if (s == 2 || n <= 2) {
        std::cout << std::min(s, n) << std::endl;
        return 0;
    }
    // общий случай:
    std::sort(all(w));
    w.pop_back();
    w.pop_back();
    std::cout << solve(w, s-2)+2 << std::endl;
    return 0;
}
