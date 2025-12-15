#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
const int mod = 998244353;
void addto(int &a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
}
int mul(int a, int b) {
    return int(a * 1LL * b % mod);
}
void solve() {    
    // читаем данные:
    std::string s, t; std::cin >> s >> t;
    // предподсчитываем степени двоек:
    vi powerOfTwo(isz(s)+1, 1);
    for (int i = 1; i <= isz(s); i++)
        powerOfTwo[i] = mul(powerOfTwo[i-1], 2);
    // предподсчитываем максимальный общий префикс для сравнений за O(1):
    vvi sameLen(isz(s)+1, vi(isz(t)+1));
    for (int i = isz(s)-1; i >= 0; i--)
        for (int j = isz(t)-1; j >= 0; j--)
            if (s[i] == t[j])
                sameLen[i][j] = 1 + sameLen[i+1][j+1];
    // запускаем динамику:
    std::vector count(isz(t)+1, std::vector<int>(isz(s)+1));
    std::vector visited(isz(t)+1, std::vector<bool>(isz(s)+1));
    std::function<int(int,int)> calc = [&](int startT, int lenS) -> int {
        if (lenS == 0) {
            // строка "s" закончилась, а "t" ещё не пуста
            return isz(t) - startT;
        }
        const int i = startT;
        // строка t уже закончилась:
        if (i >= isz(t))
            return 0;
        // проверяем вычислено ли значение:
        if (visited[i][lenS])
            return count[i][lenS];
        // вычисляем впервые: переберём размер последнего блока
        visited[i][lenS] = true;
        int result = 0;
        for (int len = 1; len <= lenS; len++) {
            int j = lenS - len;
            assert(0 <= i && i < isz(t));
            int same = sameLen[j][i];
            if (same >= len) { // блоки совпали, считаем рекурсивно
                addto(result, calc(i+len, lenS-len));
            } else {
                // блоки имеют различие до len, найдём его позицию
                // вместо цикла будем использовать нашу таблицу same для O(1):
                int lastPosT = i + same, lastPosS = j + same;
                if (lastPosT >= isz(t))
                    continue;
                if (lastPosS == lenS) {
                    // строка s закончилась, тогда как t ещё нет
                    result += isz(t) - lastPosT;
                    continue;
                }
                assert(lastPosS < lenS);
                if (s[lastPosS] > t[lastPosT])
                    continue;
                // любое разбиение префикса s длины lenS-len подойдёт
                // помножить на число способов закончить строку t
                // после нашего блока стоит перегородка
                // далее мы можем поставить любые перегородки в позициях
                // между символами на префиксе
                int cntWaysT = isz(t)-lastPosT;
                int cntWaysS = 1;
                if (int prefixLen = lenS-len; prefixLen >= 1)
                    cntWaysS = powerOfTwo[prefixLen-1];
                addto(result, mul(cntWaysS, cntWaysT));
            }
        }
        return count[i][lenS] = result;
    };
    int answ{};
    for (int i = 0; i < isz(t); i++)
        addto(answ, calc(i, isz(s)));
    std::cout << answ << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
