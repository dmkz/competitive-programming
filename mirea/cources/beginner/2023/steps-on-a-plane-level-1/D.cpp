#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем размер доски и позиции коней
    int numRows, numCols, rowWhite, colWhite, rowBlack, colBlack;
    cin >> numRows >> numCols;
    cin >> rowWhite >> colWhite;
    cin >> rowBlack >> colBlack;
    // гарантируется, что позиции различны
    // нельзя только если один из коней стоит в центре доски 3 x 3
    const bool blackInCenter = (rowBlack == 2 && colBlack == 2);
    const bool whiteInCenter = (rowWhite == 2 && colWhite == 2);
    const bool smallBoard = (numRows == 3 && numCols == 3);
    const bool cant = (blackInCenter || whiteInCenter) && smallBoard;
    cout << (cant ? "NO\n" : "YES\n");
}