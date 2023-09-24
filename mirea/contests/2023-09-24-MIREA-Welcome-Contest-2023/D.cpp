#include <bits/stdc++.h>
using namespace std;
bool isPrime(int n) {
// проверка на простоту
    for (int x = 2; x * x <= n; x++)
        if (n % x == 0)
            return false; // важно делать break здесь
    return (n > 1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        int a = n, b = n;
        // ищем ближайшее простое число сверху и снизу в цикле while
        while (!isPrime(b)) b++;
        while (!isPrime(a)) a--;
        cout << a << ' ' << b << endl;
    }
}