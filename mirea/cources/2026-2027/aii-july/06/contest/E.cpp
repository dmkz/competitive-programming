// Будем рекурсивно расставлять ферзей, двигаясь по строкам сверху вниз. Ферзь бьёт
// строку, столбец и две диагонали. Поддерживаем множество столбцов и диагоналей, которые
// находятся под боем. При переходе от row к row+1:
// 1. номера столбцов, находящихся под боем, не меняются;
// 2. номера диагоналей вида row+col сдвигаются на 1 вправо;
// 3. номера диагоналей вида row-col сдвигаются на 1 влево.
// Оптимальная скорость перебора достигается с использованием bitset и битовых сдвигов
// на один влево и на один вправо.

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> board;
vector<bitset<32>> available;
int64_t answ;

void dfs(int row, bitset<32> usedCol, bitset<32> usedDiag1, bitset<32> usedDiag2) {
    if (row == n) {
        answ++;
        return;
    }
    bitset<32> canPut = available[row] & ~(usedCol | usedDiag1 | usedDiag2);
    for (int col = 0; col < n; col++)
        if (canPut[col]) {
            // копируем состояние поля:
            bitset<32> newUsedCol = usedCol;
            bitset<32> newUsedDiag1 = usedDiag1;
            bitset<32> newUsedDiag2 = usedDiag2;
            // отмечаем текущую клетку:
            newUsedCol[col] = 1;
            newUsedDiag1[col] = 1;
            newUsedDiag2[col] = 1;
            // при переходе от row к row+1: столбцы не меняются
            newUsedDiag1 <<= 1; // все диагонали (row+col) под боем сдвигаются влево
            newUsedDiag2 >>= 1; // все диагонали (row-col) под боем сдвигаются вправо
            // рекурсивный вызов:
            dfs(row+1, newUsedCol, newUsedDiag1, newUsedDiag2);
        }
}

void solve() {
    // читаем исходные данные:
    cin >> n;
    board.resize(n);
    for (auto &it : board)
        cin >> it;
    // инициализируем вспомогательные данные:
    available.assign(n, 0);
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
            if (board[row][col] == '.')
                available[row][col] = 1;
    answ = 0;
    // запускаем рекурсивный перебор
    dfs(0, 0, 0, 0);
    // выводим ответ:
    cout << answ << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
