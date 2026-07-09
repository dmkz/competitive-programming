// сортировки, бинарный поиск, жадные алгоритмы, подпоследовательность, O(n log(n)^2)
// Задача: D, Вердикт: OK, Время: 1.720 сек, Память: 12 МБ
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
int lowpos(const auto &vec, const auto &x) {
    return int(std::lower_bound(all(vec), x) - vec.begin());
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    std::string s; std::cin >> s;
    // запоминаем позиции нулей и единиц:
    std::vector<int> pos[2]{};
    for (int i = 0; i < n; i++)
        pos[s[i] - '0'].push_back(i);
    // ищем ответ:
    int maxLen = 2, minK = 1;
    for (int k = 1; 2 * k <= n; k++) {
        // набираем максимальное количество блоков длины k
        for (int start = 0; start <= 1; start++) {
            int curr = start, p = -1, numBlocks = 0;
            // Количество блоков <= (n / k)
            // Для каждого блока: мы делаем O(log(n)) действий (можно делать O(1))
            // итоговая асимтотика: (n/1+n/2+n/3+...+n/n)*log(n)) <= n*log(n)^2
            while (true) {
                // нужно найти k символов равных curr справа от p
                int i = lowpos(pos[curr], p) + k - 1;
                if (i >= (int)pos[curr].size()) {
                    // не нашли k символов равных curr
                    break;
                }
                numBlocks++;
                p = pos[curr][i];
                curr ^= 1;
            }
            // ОЧЕНЬ ВАЖНО: длина строки должна быть > k
            if (int len = numBlocks * k; len > k) {
                if (maxLen < len) {
                    maxLen = len;
                    minK = k;
                } else if (maxLen == len) {
                    if (minK > k)
                        minK = k;
                }
            }
        }
    }
    std::cout << maxLen << ' ' << minK << std::endl;
}
