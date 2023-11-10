#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // если мы попали в какую-то букву, которая встречается
    // дважды, то это game over, мы будем бесконечно сидеть
    // в этой группе букв. Иначе мы всё время двигаемся на
    // +1 вправо. Значит все буквы, которые мы пройдём,
    // должны быть различными. Посчитаем число уникальных
    // букв. Если оно равно n, то YES
    int n; cin >> n;
    string s; cin >> s;
    sort(all(s)); // сортируем
    s.erase(unique(all(s)), s.end()); // удаляем повторы
    cout << (n == isz(s) ? "YES" : "NO");
}
