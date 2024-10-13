#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using ll = long long;
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    std::string n;
    while (std::cin >> n) {
        int k, L; std::cin >> k >> L;
        // будем считать динамику dp[len] = можно ли разбить число, состоящее из len
        // последних цифр числа n на блоки длины <= L так, чтобы каждый блок делился на k
        std::vector<bool> dp(isz(n)+1);
        dp[0] = 1;
        // переберём длину в порядке возрастания
        for (int len = 1; len <= isz(n); len++) {
            ll rem = 0;
            // для каждой длины переберём размер последнего блока
            // rem = остаток от деления текущего блока на k
            for (int block = 1; block <= L; block++) {
                if (len >= block) {
                    rem = (rem * 10LL + (n[isz(n)-(len-block)-1] - '0')) % k;
                    // можно если остаток блока равен 0 и оставшиеся len-block символов
                    // можно разбить на блоки по тем же правилам
                    dp[len] = dp[len] || (rem == 0 && dp[len-block]);
                }
            }
        }
        // найдём остаток от деления числа n на число k:
        ll total = 0;
        for (int i = 0; i < isz(n); i++)
            total = (total * 10 + (n[i] - '0')) % k;
        // проверка по правилам задачи должна совпадать с правилами математики:
        std::cout << (dp[isz(n)] == (total == 0)) << "\n";
    }
}
