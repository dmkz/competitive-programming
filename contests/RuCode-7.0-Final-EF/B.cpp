#include <bits/stdc++.h>
#define isz(x) (int)(x).size()

using namespace std;
using ld = long double;
using pii = pair<int, int>;
using ll = long long;

void research(int n) {
// данная функция проверяет все четвёрки на мелких числах в поисках закономерностей
    vector<ld> fib{1,2};
    for (int i = 2; i <= n; i++)
        fib.push_back(fib[i-1]+fib[i-2]);
    set<ld> s;
    for (int i = 0; i < isz(fib); i++)
        for (int j = i+1; j < isz(fib); j++)
            for (int k = j+1; k < isz(fib); k++)
                for (int f = k+1; f < isz(fib); f++) {
                    if (fib[f] >= fib[k] + fib[j] + fib[i]) {
                        break;
                    }
                    s.insert(fib[f] + fib[k] + fib[j] + fib[i]);
                }
    // выводим:
    int i = 1;
    for (auto item : s) {
        cout << i << ": " << item << endl;
        i++;
    }
}

int main()
{
    // research(20);
    // закономерность:
    // 11
    // 17 18
    // 27 28 29
    // 43 44 45 47
    // 69 70 71 73 76
    // ...
    // определяем ряд и место в этом ряду:
    int n; cin >> n;
    n--;
    int row = 1;
    while (n >= row) { n -= row; row++; }
    int col = n;
    // считаем числа фибоначчи:
    const int mod = 998244353;
    vector<int64_t> fib(100000, 1);
    for (int i = 2; i < isz(fib); i++)
        fib[i] = (fib[i-1] + fib[i-2]) % mod;
    // считаем ответ на основе ряда и места в ряду:
    int64_t number = (fib[row+3] * 2 + 1) % mod;
    for (int j = 1; j <= col; j++)
        (number += fib[j-1]) %= mod;
    cout << number << endl;
}
