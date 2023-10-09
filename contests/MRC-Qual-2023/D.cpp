#include <bits/stdc++.h>
#define int int64_t
using namespace std;
int32_t main() {
    // 1, 7, 7^2, 7^3
    // похоже, ответ - количество делителей между первым и вторым числом
    int q, r; cin >> q >> r;
    int n = q * r - q, answ = 0;
    for (int x = 1; x * x <= n; x++)
        if (int y = n / x; y * x == n)
            answ += 1 + (x != y);
    cout << answ << endl;
}
