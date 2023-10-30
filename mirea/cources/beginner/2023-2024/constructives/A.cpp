#include <bits/stdc++.h>
using namespace std;
main() {
    // в качестве "a" можно взять "g", а остаток суммы взять в качестве "b"
    int s, g; cin >> s >> g;
    int a = g, b = s - g;
    if (a > 0 && b > 0 && gcd(a,b) == g)
        cout << a << " " << b << "\n";
    else
        cout << "-1\n";
}
