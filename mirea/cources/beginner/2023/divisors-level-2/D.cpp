#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    // преобразуем уравнение, добавив слева и справа 1:
    // xy+x+y=n => xy+x+y+1=n+1 => (x+1)(y+1) = n+1
    // выходит, что количество решений столько, сколько делителей у n+1
    n++;
    int nDivisors = 0;
    for (int x = 1; x * x <= n; x++)
        if (int y = n / x; x * y == n)
            nDivisors += ((x == y) ? 1 : 2);
    // выводим ответ:
    cout << nDivisors << '\n';
}