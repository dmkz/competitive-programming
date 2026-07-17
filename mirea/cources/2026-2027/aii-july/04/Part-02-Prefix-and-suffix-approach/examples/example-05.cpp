// Пример: удалить один элемент так, чтобы НОД оставшихся был максимальным.
// Ввод: n и массив чисел.
// Вывод: максимальный возможный НОД после удаления ровно одного элемента.

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // Работаем в 1-индексации и добавляем нули по краям,
    // чтобы одна и та же формула подходила для всех i.
    vector<long long> pref(n + 2, 0), suff(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        pref[i] = gcd(pref[i - 1], a[i]);
    }
    for (int i = n; i >= 1; i--) {
        suff[i] = gcd(a[i], suff[i + 1]);
    }

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, gcd(pref[i - 1], suff[i + 1]));
    }

    cout << answer << '\n';
    return 0;
}
