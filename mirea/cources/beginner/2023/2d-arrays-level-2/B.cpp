#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int main() {
    int nRows, nCols; 
    cin >> nRows >> nCols;
    // начиная с C++17 шаблонный тип может быть выведен автоматически
    // в данном случае тип выводится из второго параметра конструктора
    // то есть здесь создаётся вектор векторов из интов:
    vector map(nRows, vector<int>(nCols));
    // надо найти минимум в каждой строке и среди всех них взять максимум
    vector<int> min_in_row(nRows);
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            cin >> map[row][col];
        }
        min_in_row[row] = *min_element(all(map[row]));
    }
    cout << *max_element(all(min_in_row)) << endl;
    
    return 0;
}