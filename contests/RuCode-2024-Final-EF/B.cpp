#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // для каждого номера посчитаем в скольки строках он встречается
    // и в каких строках именно он встречается
    // сначала будем выбирать те, которые в трёх строках
    // затем по две строки
    // затем по одной строке
    int n, k;
    cin >> n >> k;
    vvi cnt(1+5e5);
    vi minForRow(3, k);
    for (int row = 0; row < 3; row++) {
        for (int i = 0; i < n; i++) {
            int a; cin >> a;
            cnt[a].push_back(row);
        }
    }
    int answ = 0;
    for (int numRows = 3; numRows >= 1; numRows--) {
        for (int number = 1; number <= 5e5; number++) {
            if (cnt[number].size() == numRows) {
                bool need = false;
                for (auto id : cnt[number])
                    need |= (minForRow[id] > 0);
                if (need) {
                    answ++;
                    for (auto id : cnt[number])
                        if (minForRow[id] > 0)
                            minForRow[id]--;
                }
            }
        }
    }
    cout << answ << endl;
}
