#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        // ищем максимальный делитель числа n
        // достаточно пробежать до корня из n
        // если число делится на x, то делится и на n / x
        // обновляем ответ за счёт n / x
        int answ = 1;
        for (int x = 2; x * x <= n; x++)
            if (n % x == 0)
                answ = max(answ, n / x);
        cout << answ << endl;
    }
}