#include <bits/stdc++.h>
using namespace std;
int main() {
    // ускорение ввода-вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем запросы и отвечаем на них:
    int tt; cin >> tt;
    while (tt --> 0) {
        // оптимальнее всего по объёму делать куб, то есть стороны брать L / 3
        // но L может не делиться на 3, поэтому оставшиеся добираем L / 3 + 1
        int L; cin >> L;
        int a = L / 3;
        int b = a + (L % 3 >= 1);
        int c = a + (L % 3 >= 2);
        // считаем объём (в типе long long) и выводим его:
        long long V = a * 1LL * c * b;
        cout << V << '\n';
    }
    return 0;
}