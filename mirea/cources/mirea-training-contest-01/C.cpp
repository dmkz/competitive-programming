#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(12);
    int a, b; cin >> a >> b;
    if (atan2l(b, a) > atan2l(1, 1)) {
        cout << "-1\n";
        return 0;
    }
    long double m = (a + b) / sqrtl(2);
    m /= sqrtl(2);
    // x = m / k >= b
    // k <= m / b
    int k = m / b;
    long double x = m / k;
    cout << x << endl;
}
