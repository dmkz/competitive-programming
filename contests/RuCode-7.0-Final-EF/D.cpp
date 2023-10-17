#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, answ = 0; cin >> n;
    while (n --> 0) {
        string s; cin >> s;
        s += "00";
        // считаем число нулей на конце числа - все они превратятся в девятки
        while (s.size() && s.back() == '0') {
            answ++;
            s.pop_back();
        }
        // на конце могла остаться одна девятка, которая станет 8, и её надо вычесть
        if (s.size() && s.back() == '9')
            answ--;
    }
    cout << answ << endl;
}
