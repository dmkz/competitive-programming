#include <bits/stdc++.h>
using namespace std;
int main() {
    // ответ: младший единичный бит числа, или -1, если число равно 0
    // функция ffs (Find First Signed) находит младший единичный бит
    int tt; cin >> tt;
    while (tt --> 0) {
        int x; cin >> x;
        int res = __builtin_ffs(x);
        cout << res-1 << '\n';
    }
    return 0;
}
