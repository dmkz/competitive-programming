#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using vpii = vector<pii>;
main() {
    vector a(8, string{});
    for (auto &row : a)
        cin >> row;
    auto small = a;
    auto big = a;
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (a[r][c] == '.') {
                small[r][c] = '?';
                big[r][c] = '?';
                continue;
            } else if (isupper(a[r][c])) {
                big[r][c] = a[r][c];
                small[r][c] = '?';
            } else {
                small[r][c] = a[r][c];
                big[r][c] = '?';
            }
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) {
            auto setToField = [&](int row, int col, char what) {
                if (row < 0 || row > 7 || col < 0 || col > 7)
                    return;
                if (isupper(a[r][c]))
                    big[row][col] = what;
                else
                    small[row][col] = what;
            };
            if (a[r][c] == 'r' || a[r][c] == 'R') {
                // ладья
                for (auto [dr,dc] : vpii{{-1, 0}, {+1, 0}, {0, -1}, {0, +1}}) {
                    int row = r + dr;
                    int col = c + dc;
                    while (row >= 0 && row < 8 && col >= 0 && col < 8
                        && a[row][col] == '.') {
                            setToField(row, col, '.');
                            row += dr;
                            col += dc;
                        }
                    if (row >= 0 && row < 8 && col >= 0 && col < 8)
                        setToField(row, col, a[row][col]);
                }
            } else if (a[r][c] == 'n' || a[r][c] == 'N') {
                // конь
                for (auto [dr,dc] : vpii{{-2, -1}, {-2, +1}, {+2, -1}, {+2, +1},
                                         {-1, -2}, {+1, -2}, {-1, +2}, {+1, +2}})
                {
                    int row = r + dr;
                    int col = c + dc;
                    if (row >= 0 && row < 8 && col >= 0 && col < 8)
                        setToField(row, col, a[row][col]);
                }
            } else if (a[r][c] == 'b' || a[r][c] == 'B') {
                // слон
                for (auto [dr,dc] : vpii{{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}}) {
                    int row = r + dr;
                    int col = c + dc;
                    while (row >= 0 && row < 8 && col >= 0 && col < 8
                        && a[row][col] == '.') {
                            setToField(row, col, '.');
                            row += dr;
                            col += dc;
                        }
                    if (row >= 0 && row < 8 && col >= 0 && col < 8)
                        setToField(row, col, a[row][col]);
                }
            } else if (a[r][c] == 'q' || a[r][c] == 'Q') {
                // ферзь
                for (int dr = -1; dr <= 1; dr++)
                    for (int dc = -1; dc <= 1; dc++)
                        if (dr * dr + dc * dc > 0) {
                            int row = r + dr;
                            int col = c + dc;
                            while (row >= 0 && row < 8 && col >= 0 && col < 8
                                && a[row][col] == '.') {
                                    setToField(row, col, '.');
                                row += dr;
                                col += dc;
                            }
                            if (row >= 0 && row < 8 && col >= 0 && col < 8)
                                setToField(row, col, a[row][col]);
                        }
            } else if (a[r][c] == 'k' || a[r][c] == 'K') {
                // король
                for (int dr = -1; dr <= 1; dr++)
                    for (int dc = -1; dc <= 1; dc++)
                        if (dr * dr + dc * dc > 0) {
                            int row = r + dr;
                            int col = c + dc;
                            if (row >= 0 && row < 8 && col >= 0 && col < 8)
                                setToField(row, col, a[row][col]);
                        }
            } else if (a[r][c] == 'p') {
                // пешка вверх
                for (int dc = -1; dc <= 1; dc++) {
                    int row = r - 1, col = c + dc;
                    if (row >= 0 && row < 8 && col >= 0 && col < 8)
                        setToField(row, col, a[row][col]);
                }
            } else if (a[r][c] == 'P') {
                // пешка вниз
                for (int dc = -1; dc <= 1; dc++) {
                    int row = r + 1, col = c + dc;
                    if (row >= 0 && row < 8 && col >= 0 && col < 8)
                        setToField(row, col, a[row][col]);
                }
            }
        }
    // выводим ответ
    for (auto &row : small)
        cout << row << "\n";
    cout << endl;
    for (auto &row : big)
        cout << row << "\n";
    cout << endl;
}
