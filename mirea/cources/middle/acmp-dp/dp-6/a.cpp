#include <bits/stdc++.h>
using ll = long long;
#define int ll
using namespace std;
string f(int n, int a, int b) {
    if (n > 0) {
        // надо добиться нуля в двоичной записи
        // ставим 1 или 2
        // должно быть (a + b * разряд) % 2 == 0
        if ((a + b * 1) % 2 == 0) {
            return f(n-1, (a + b * 1) / 2, b * 5) + "1";
        } else {
            assert((a+b*2)%2 == 0);
            return f(n-1, (a+b*2)/2, b*5) + "2";
        }
    }
    return "1";
}
signed main() {
    //int n; cin >> n;
    //cout << f(n, 0, 1) << endl;
    int x = 717;
    assert(x == 0b1011001101);
    cout << x << endl;
    cout << 0b1011001101 << endl;
}
