// Пример: Школа танцев.
// Ввод: n и строка из двух типов символов, описывающая ряд учеников.
// Вывод: количество подотрезков, где учеников двух типов поровну.

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    // Считаем, что символ 'a' даёт вклад +1,
    // а любой другой символ даёт вклад -1.
    map<int, int> cnt;
    cnt[0] = 1;

    int balance = 0;
    long long answer = 0;
    for (char ch : s) {
        balance += (ch == 'a' ? 1 : -1);
        answer += cnt[balance];
        cnt[balance]++;
    }

    cout << answer << '\n';
    return 0;
}