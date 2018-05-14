#include <bits/stdc++.h>

using namespace std;

int main() {
//    freopen("input.txt", "rt", stdin);
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int nRows, nCols, nQueries;
    cin >> nRows >> nCols >> nQueries;
    
    vector<string> field(nRows);
    for (int row = 0; row < nRows; ++row) {
        cin >> field[row];
    }
    
    vector<vector<int>> colors(nRows, vector<int>(nCols, -1));
    vector<int> count;
    
    function<void(int, int, int)> calc = [&](int row, int col, int color) {
        colors[row][col] = color;
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr * dr + dc * dc == 1) {
                    if (field[row+dr][col+dc] == '*') {
                        count[color]++;
                    } else if (colors[row+dr][col+dc] != color) {
                        calc(row+dr, col+dc, color);
                    }
                }
            }
        }
    };
    
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            if (field[row][col] == '.' && colors[row][col] == -1) {
                int color = (int)count.size();
                count.push_back(0);
                calc(row, col, color);
            }
        }
    }
    
    for (int q = 0; q < nQueries; ++q) {
        int row, col;
        cin >> row >> col;
        --row, --col;
        cout << count[colors[row][col]] << "\n";
    }
    
    return 0;
}