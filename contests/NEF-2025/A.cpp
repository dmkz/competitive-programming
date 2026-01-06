// математика, неравенства, строки
#include <bits/stdc++.h>
using ll = long long;
const ll inf = (ll)1e12+7;
main() {
    // для начала прочитаем все слова и для каждого слова, для каждой буквы посчитаем
    // её количество в нём, а также суммарное количество каждой буквы по всем словам
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m; std::cin >> n >> m;
    std::vector<ll> totalLetterCount(26);
    std::vector<std::string> words(n);
    std::vector<std::array<ll, 26>> letterCount(n);
    for (int i = 0; i < n; i++) {
        std::cin >> words[i];
        for (auto it : words[i]) {
            assert('A' <= it && it <= 'Z');
            totalLetterCount[it - 'A']++;
            letterCount[i][it - 'A']++;
        }
    }
    // Теперь мы готовы решать задачу.
    // Для каждой буквы ответ независим. Неравенство для текущей буквы:
    // k * (cnt1 + cnt2 + ... + cntN - cntI) + cntI <= m * (totalCnt - cntI)
    // Упростим и найдём максимальное k:
    // k * (totalCnt - cntI) + cntI <= m * (totalCnt - cntI)
    // k <= (m * (totalCnt - cntI) - cntI) / (totalCnt - cntI)
    // i-й ответ: минимум из максимальных k для каждой группы
    for (int i = 0; i < n; i++) {
        ll minK = inf;
        for (int j = 0; j < 26; j++) {
            ll p = m * totalLetterCount[j] - (m+1) * letterCount[i][j];
            ll q = totalLetterCount[j] - letterCount[i][j];
            if (p < 0) // числитель отрицательный, значит букв не хватит
                minK = -1;
            else if (q != 0) // j-я буква нужна, обновляем k:
                minK = std::min(minK, p / q);
        }
        std::cout << minK << ' ';
    }
    std::cout << std::endl;
}
