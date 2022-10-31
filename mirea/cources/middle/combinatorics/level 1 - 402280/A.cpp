#include <bits/stdc++.h>
using namespace std;

const int mod = (int)(1e9+7); // 1'000'000'000+7

int binpow(int a, int64_t n) {
    if (n == 0)
        return 1;
    // n > 0
    if (a == 1)
        return 1;
    // a = a * 1LL * a;
    if (n % 2 == 0) // чёт
        return binpow(int(a * 1LL * a % mod), n / 2);
    return int(a * 1LL * binpow(a, n-1) % mod);
}

int main() {
    int a, n;
    cin >> a >> n;
    cout << binpow(a, n);
}