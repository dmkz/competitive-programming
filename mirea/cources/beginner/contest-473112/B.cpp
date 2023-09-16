#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
int main() {
    int nRows, nCols;
    cin >> nRows >> nCols;
    vector a(nRows, string(nCols, '.'));
    for (auto &it : a) cin >> it;
    // сначала определим какие строки и столбцы в каких операциях участвовали
    vi operationCol(nCols), operationRow(nRows);
    int countOperations = 0, ok = 1;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] == '#') {
                // r и c были в одной операции
                if (operationRow[r]) {
                    if (operationCol[c]) {                       
                        ok &= (operationRow[r] == operationCol[c]);
                    } else {
                        operationCol[c] = operationRow[r];
                    }
                } else {
                    if (operationCol[c]) {
                        operationRow[r] = operationCol[c];
                    } else {
                        countOperations++;
                        operationRow[r] = countOperations;
                        operationCol[c] = countOperations;
                    }
                }
            }
    vvi rows(countOperations+1), cols(countOperations+1);
    for (int i = 0; i < nRows; i++)
        rows[operationRow[i]].push_back(i);
    for (int i = 0; i < nCols; i++)
        cols[operationCol[i]].push_back(i);
    // теперь выполним все операции и сравним то, что получилось, с тем, что дано
    vector b(nRows, string(nCols, '.'));
    for (int id = 1; id <= countOperations; id++)
        for (int r : rows[id])
            for (int c : cols[id])
                b[r][c] = '#';
    // выводим ответ
    cout << (a == b && ok ? "Yes\n" : "No\n");
}
