// динамическое программирование, стек, O(n*m)
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных
    int nRows, nCols; cin >> nRows >> nCols;
    vector a(nRows, vector<char>(nCols+1, '0'));
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            cin >> a[r][c];
    // решение
    int answ = 0;
    vector<int> colLen(nCols+1); // colLen[i] = высота столбца из '1'
    for (int r = 0; r < nRows; r++) {
        // в стеке храним пары (высота столбца, его номер)
        vector<pair<int,int>> stack{{0,-1}};
        for (int c = 0; c <= nCols; c++) {
            // обновляем высоту столбца
            colLen[c] = (a[r][c] == '1') * (colLen[c] + 1);
            // обновляем ответ
            while (colLen[c] < stack.back().first) {
                // мы удалим верхушку стека, посчитав площадь
                // прямоугольника, образованного им: между текущим
                // столбцом и предыдущей вершиной стека
                auto [lastH, lastI] = stack.back();
                stack.pop_back();
                auto [prevH, prevI] = stack.back();
                answ = max(answ, lastH * (c - prevI - 1));
            }
            // обновляем стек
            stack.emplace_back(colLen[c], c);
        }
    }
    cout << answ << endl;
}
