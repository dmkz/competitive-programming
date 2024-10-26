#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
// выводим:
// 1 ... 9
// 10 ... 99
// 100 ... 999
// 1000 ... 9999
main() {
    int n;
    while (cin >> n) {
        string nn = to_string(n);
        int answ = 0;
        for (int start = 1; start <= n; start*=10) {
            int finish = start * 10 - 1;
            if (finish > n)
                finish = n;
            // выводим номера одинаковой длины группами по 500
            // (с округлением вверх)
            answ += (finish - start + 1 + 499) / 500;
        }
        cout << answ << endl;
    }
}
