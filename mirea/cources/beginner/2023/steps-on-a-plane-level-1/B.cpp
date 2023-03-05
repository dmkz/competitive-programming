#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем клетку где король:
    char column, row;
    cin >> column >> row;
    // смотрим, в какие столбцы может перейти король:
    const int minCol = max(0, column - 'a' - 1); // предыдущий столбец
    const int maxCol = min(7, column - 'a' + 1); //  следующий столбец
    // смотрим, в какие строки может перейти король:
    const int minRow = max(0, row - '1' - 1); // предыдущая строка
    const int maxRow = min(7, row - '1' + 1); // следующая строка
    // король может сделать ход и он останется в прямоугольнике
    // [minRow ... maxRow] x [minCol ... maxCol]
    // тогда ответ: площадь прямоугольника минус 1 (клетка, где он находится
    const int square = (maxRow - minRow + 1) * (maxCol - minCol + 1);
    cout << square - 1;
}