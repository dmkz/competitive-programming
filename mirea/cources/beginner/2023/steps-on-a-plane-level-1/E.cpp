#include <bits/stdc++.h>
using namespace std;
int main() {
    int numTests; cin >> numTests;
    while (numTests --> 0) {
        int col1, row1, col2, row2;
        cin >> col1 >> row1 >> col2 >> row2;
        // по условию задачи всегда col1 < col2 и row1 < row2
        string answ;
        // намотаем два круга против часовой
        for (int round = 0; round <= 1; round++) {
            // Стоим в S. Идём в T:
            answ += string(round, 'D'); // вниз, если надо
            answ += string(col2-col1+round, 'R'); // вправо
            answ += string(row2-row1+round, 'U'); // вверх
            answ += string(round, 'L'); // влево, если надо
            // Стоим в T. Идём в S:
            answ += string(round, 'U'); // вверх, если надо
            answ += string(col2-col1+round, 'L'); // влево
            answ += string(row2-row1+round, 'D'); // вниз
            answ += string(round, 'R'); // вправо, если надо
        }
        cout << answ << '\n';
    }
}