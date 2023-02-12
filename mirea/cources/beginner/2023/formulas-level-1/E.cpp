#include <bits/stdc++.h>
using namespace std;
int main() {
    int64_t n, a, b, p, q;
    cin >> n >> a >> b >> p >> q;
    // делятся на a и b одновременно: делятся на НОК(a,b) = lcm(a,b)
    // LCM = least common multiple (or lowest common multiple)
    // т.е. НОК на английском - есть такая функция в C++ (НОД = gcd)
    int64_t nAB = n / lcm(a,b); // формула учитывает, что нет нулевой доски
                                // если бы она была, надо было +1 сделать
    // делятся на a, но не на b: (из всех nA исключить nAB)
    int64_t nA = n / a - nAB;
    // делятся на b, но не на a: (из всех nB исключить nAB)
    int64_t nB = n / b - nAB;
    // ответ: элементы в пересечении (nAB) красим лучшим образом
    cout << nA * p + nB * q + max(p,q)*nAB << endl;
}