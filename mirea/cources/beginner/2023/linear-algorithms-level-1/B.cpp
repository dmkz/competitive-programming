#include <bits/stdc++.h>
using namespace std;
int main() {
    // нам надо знать только сумму чисел и n, чтобы сказать,
    // сколько пуговиц реально застёгнуто
    int n, sum{};
    cin >> n;
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        sum += a;
    }
    bool yes = (n == 1 && sum == 1) || (n > 1 && sum == n-1);
    cout << (yes ? "YES\n" : "NO\n");
}