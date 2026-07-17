// Пример: количество каждой буквы от 'a' до 'z' на подотрезке.
// Ввод: строка s, затем q запросов [l, r] в единичной индексации.
// Вывод: для каждого запроса 26 чисел - количества букв 'a'..'z' на отрезке.

#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = static_cast<int>(s.size());

    int q;
    cin >> q;

    // pref[i][c] хранит количество буквы c среди первых i символов строки.
    vector<array<int, 26>> pref(n + 1);
    pref[0].fill(0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i];
        pref[i + 1][s[i] - 'a']++;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;

        // Ответ для каждой буквы - разность двух префиксных состояний.
        for (int c = 0; c < 26; c++) {
            if (c) {
                cout << ' ';
            }
            cout << pref[r + 1][c] - pref[l][c];
        }
        cout << '\n';
    }

    return 0;
}