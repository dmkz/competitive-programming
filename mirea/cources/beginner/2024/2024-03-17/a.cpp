#include <bits/stdc++.h>
using namespace std;
int main() {
    // позиция слона - центр креста
    int tt; cin >> tt;
    while (tt --> 0) {
        // читаем поле
        int n = 8;
        vector<string> a(n);
        for (auto &it : a)
            cin >> it;
        // ищем слона
        int ansRow = -1, ansCol = -1;
        for (int r = 1; r + 1 < n; r++)
            for (int c = 1; c + 1 < n; c++) {
                bool ok = (a[r][c] == '#' &&
                           a[r-1][c-1] == '#' && a[r-1][c+1] == '#' &&
                           a[r+1][c-1] == '#' && a[r+1][c+1] == '#');
                if (ok) {
                    ansRow = r;
                    ansCol = c;
                }
            }
        cout << ansRow+1 << " " << ansCol+1 << "\n";
    }
}
