#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
using vi = std::vector<int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vvpii = std::vector<vpii>;
// умножение двух чисел с отслеживанием переполнения
// если переполнилось, то результат равен INF
const int INF = (int)1e9+7;
int multiply(int a, int b) { return (a < INF / b) ? a * b : INF; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, d; std::cin >> n >> d;
    vi a(n);
    for (auto &it : a)
        std::cin >> it;
    if (d == 0) {
        // берём все числа и смотрим остаток 0 или нет
        int rem = 1;
        for (auto &it : a)
            rem = rem * it % 10;
        if (rem == 0) {
            std::cout << n << "\n";
            for (auto it : a)
                std::cout << it << ' ';
            std::cout << std::endl;
            return 0;
        }
        std::cout << "-1\n";
        return 0;
    }
    // выкинем некоторые числа. Таблица периодичности по модулю 10:
    // 1: 1, 1, 1, 1, 1, 1, ...
    // 2: 1, 2, 4, 8, 6, 2, ...
    // 3: 1, 3, 9, 7, 1, ...
    // 4: 1, 4, 6, 4, ...
    // 5: 1, 5, 5, 5, ...
    // 6: 1, 6, 6, 6, ...
    // 7: 1, 7, 9, 3, 1, ...
    // 8: 1, 8, 4, 2, 6, ...
    // 9: 1, 9, 1, ...
    // надо выкинуть чётные, если d - нечётное, типо если хотя бы раз умножим на 2,
    // то нечётное больше никогда-никогда не получим
    // и выкинем пятёрки, если d не делится на 5, аналогично, любая нечётная цифра,
    // умноженная на 5, это 5
    if (d % 5 != 0) {
        auto it = std::remove_if(all(a), [&](int x){return x % 5 == 0; });
        a.erase(it, a.end());
    }
    if (d % 2 != 0) {
        auto it = std::remove_if(all(a), [&](int x){return x % 2 == 0; });
        a.erase(it, a.end());
    }
    if (!isz(a)) {
        std::cout << "-1\n";
        return 0;
    }
    // теперь берём все числа и будем выкидывать лишние
    // так как порядок равен 4, то из любой цифры в любую другую мы можем
    // прийти за <= 3 выкидывания
    // пусть P = произведение всех чисел. Распишем, что будет после выкидывания,
    // и какой вариант лучший:
    // P / x > P / y <=> y > x
    // похоже надо выкинуть минимальное произведение
    vvpii dp(isz(a), vpii(10, {INF, 0}));
    // dp[i][остаток после удаления] = минимальное произведение удаляемых трёх чисел чтобы получить этот остаток rem
    // инициализация:
    dp[0][1] = {a[0], -1};
    setmin(dp[0][a[0]%10], pii{1, 1});
    // переходы:
    for (int i = 1; i < isz(a); i++) {
        for (int was = 0; was < 10; was++) {
            if (dp[i-1][was].first < INF) {
                // удолим
                if (a[i] % 10 != 1)
                    setmin(dp[i][was], pii{multiply(dp[i-1][was].first, a[i]), -1});
                // не удолим
                setmin(dp[i][was*a[i]%10], pii{dp[i-1][was].first, was});
            }
        }
    }
    // восстановление ответа:
    if (dp[isz(a)-1][d].first >= INF) {
        std::cout << "-1\n";
        return 0;
    }
    vi needToRemove = {};
    for (int i = isz(a)-1; i >= 0; i--) {
        auto [prod, prev] = dp[i][d];
        if (prev == -1) needToRemove.push_back(a[i]);
        else d = prev;        
    }
    std::sort(all(a));
    for (auto it : needToRemove)
        a.erase(std::lower_bound(all(a), it));
    std::cout << isz(a) << "\n";
    for (auto it : a)
        std::cout << it << ' ';
    std::cout << std::endl;
}
