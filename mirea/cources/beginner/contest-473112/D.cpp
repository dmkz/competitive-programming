#include <bits/stdc++.h>
using namespace std;
void remax(auto &x, const auto &y) { if (x < y) x = y; }
int main() {
    // заменяем 0 на -1, а 1 на +1
    // тогда нужно найти отрезок, сумма на котором равна нулю
    int n; cin >> n;
    string s; std::cin >> s;
    map<int, int> firstPos;
    firstPos[0] = -1;
    int balance = 0, answ = 0;
    for (int i = 0; i < n; i++) {
        balance += (s[i] == '1' ? +1 : -1);
        if (auto it = firstPos.find(balance); it == firstPos.end())
            firstPos[balance] = i;
        remax(answ, i - firstPos[balance]);
    }
    cout << answ << endl;
}
