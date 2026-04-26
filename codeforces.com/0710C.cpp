// конструктив, чётность
#include <bits/stdc++.h>
using namespace std;
main() {
    // сгруппируем числа по чётности
    int n; cin >> n;
    vector<int> nums[2]{};
    for (int i = 1; i <= n * n; i++)
        nums[i % 2].push_back(i);
    // нечётные числа ставим в форме ромба
    // в остальные клетки ставим чётные числа
    int centerRow = n/2, centerCol = n/2, requiredDist = n/2;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int dist = abs(r - centerRow) + abs(c - centerCol);
            int item;
            if (dist <= requiredDist) {
                item = nums[1].back();
                nums[1].pop_back();
            } else {
                item = nums[0].back();
                nums[0].pop_back();
            }
            cout << item << ' ';
        }
        cout << '\n';
    }
}