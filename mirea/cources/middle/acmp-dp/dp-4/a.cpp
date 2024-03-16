// это комбинаторное решение
#include <bits/stdc++.h>
using namespace std;
using ll = __int128;
ll C(int n, int k) {
    if (n - k < k)
        return C(n, n-k);
    if (n < 0 || k > n)
        return 0;
    ll res = 1;
    for (int i = 1; i <= k; i++) {
        res *= (n - i + 1);
        res /= i;
    }
    return res;
}
ostream &operator<<(ostream &os, __int128 x) {
    if (x < 0) { os << "-"; x = -x; }
    string stack;
    do {
        stack += char('0' + x % 10);
        x /= 10;
    } while (x > 0);
    reverse(stack.begin(), stack.end());
    return os << stack;
}
int main() {
    int n, a, b; cin >> n >> a >> b;
    ll waysA = C(n+a, a), waysB = C(n+b, b);
    cout << waysA * waysB << endl;
}
