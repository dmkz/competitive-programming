#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, k; cin >> n >> k;
    // сначала просто разобьём число n на k слагамых (примерно равных)
    // n = q * k + r, 0 <= r < k
    int q = n / k;
    int r = n % k;
    vector<int> answer(k, q); // k чисел равных q, т.е. n / k
    // осталось добавить r единиц
    for (int index = 0; index < r; index++)
        answer[index]++;
    // теперь у нас r и k-r чисел разной чётности
    // если одно из этих чисел чётное, то мы можем это сделать,
    // так как за одно перекидывание единицы мы можем изменить чётность
    // ровно двух чисел
    bool ok = false;
    if (r == 0) {
        // всё в порядке, все числа одной чётности
        ok = true;
    } else if (r % 2 == 0 && answer.front() > 1) {
        ok = true;
        // меняем чётность первых r чисел
        for (int L = 0, R = r-1; L < R; L++, R--)
            answer[L]--, answer[R]++;
    } else if ((k - r) % 2 == 0 && answer.back() > 1) {
        ok = true;
        // меняем чётность последних (k - r) чисел
        for (int L = r, R = k-1; L < R; L++, R--)
            answer[L]++, answer[R]--;
    }
    if (ok) {
        cout << "YES\n";
        for (auto it : answer)
            cout << it << ' ';
        cout << '\n';
    } else
        cout << "NO\n";
}
main() {
    // ускорение ввода-вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    // мультитесты
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
