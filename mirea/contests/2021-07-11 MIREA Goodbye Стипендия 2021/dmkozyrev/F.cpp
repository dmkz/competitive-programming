#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем входные данные
    int n,m,k; std::cin >> n >> m >> k;
    vvi a(n, vi(m));
    for (int i = 0; i < n; i++) {
        std::string s; std::cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j] - '0';
        }
    }
    // начинаем решать задачу
    // перебираем все возможные подмножества горизонтальных разрезов
    // их 2^(n-1)
    // для каждого подмножества горизонтальных ищем минимальное подмножество
    // вертикальных разрезов жадно
    int answ = (n-1)+(m-1);
    for (int mask = 0; mask < (1 << (n-1)); mask++) {
        // для каждой строки определяем номер блока
        vi idBlock(n);
        for (int i = 1; i < n; i++) {
            if ((mask >> (i-1)) & 1) {
                idBlock[i] = idBlock[i-1] + 1;
            } else {
                idBlock[i] = idBlock[i-1];
            }
        }
        // текущая сумма внутри блока
        vi currSum(idBlock.back()+1);
        // добавление столбца
        auto addColumn = [&](int col) {
            for (int row = 0; row < n; row++) {
                currSum[idBlock[row]] += a[row][col];
            }
        };
        // удаление столбца
        auto remColumn = [&](int col) {
            for (int row = 0; row < n; row++) {
                currSum[idBlock[row]] -= a[row][col];
            }
        };
        // проверим на то, можем ли мы хоть какой-то разрез вертикальными сделать:
        bool can = true;
        for (int col = 0; can && col < m; col++) {
            addColumn(col);
            if (*std::max_element(all(currSum)) > k) {
                can = false;
            }
            remColumn(col);
        }
        if (!can) continue;
        // если можем хоть какой-то, то находим минимальный из возможных жадно:
        int currAnsw = __builtin_popcount(mask);
        for (int col = 0; col < m; col++) {
            addColumn(col);
            if (*std::max_element(all(currSum)) > k) {
                currAnsw++;
                std::fill(all(currSum),0);
                addColumn(col);
            }
        }
        answ = std::min(answ,currAnsw);
    }
    std::cout << answ << std::endl;
    return 0;
}