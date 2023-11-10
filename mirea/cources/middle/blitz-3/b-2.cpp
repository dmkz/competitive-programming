#include <bits/stdc++.h>
using namespace std;
string solve(int64_t a, int64_t b, int64_t c) {
    if (a * c % b == 0)
        return "YES";
    // если "c" содержит все простые, которые есть в "b", то YES
    // пересечь множества простых можно с использованием gcd
    while (true) {
        int64_t g = gcd(c, b);
        // "g" содержит все простые, которые есть одновременно и
        // в "c", и в "b"
        if (g == 1)
            break;
        // делим "b" пока делится на "g"
        b /= g;
        while (b % g == 0)
            b /= g;
        // как минимум на одно простое в числе "b" стало меньше
        // процесс повторяется пока общие простые не кончатся
    }
    // если b == 1, то простые закончились
    return b == 1 ? "YES" : "NO";
}
int main() {
    int64_t a, b, c;
    cin >> a >> b >> c;
    cout << solve(a,b,c);
}
