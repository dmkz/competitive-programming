#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<string> a(n);
    for (auto &s : a)
        cin >> s;
    // от каждой клетки считаем, сколько единиц вверх и влево, а также
    // сторону максимального квадрата с правым нижним углом в этой клетке
    vector up(n, vector(n, 0));
    auto left = up;
    auto square = left;
    int answ = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (a[row][col] == '1') {
                // кол-во единиц вверх:
                int U = up[row][col] = 1 + (row-1 >= 0 ? up[row-1][col] : 0);
                // кол-во единиц влево:
                int L = left[row][col] = 1 + (col-1 >= 0 ? left[row][col-1] : 0);
                // максимальная сторона квадрата выбирается как минимум из:
                // квадрата на одну клетку выше и левее, +1
                // максимальной полосы единиц вверх
                // максимальной полосы единиц влево
                int S = 1 + (row-1>=0&&col-1>=0?square[row-1][col-1]:0);
                int res = square[row][col] = min({U,L,S});
                if (answ < res * res)
                    answ = res * res;
            }
        }
    }
    cout << answ << endl;
}
