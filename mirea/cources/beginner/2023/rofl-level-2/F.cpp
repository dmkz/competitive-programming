#include <bits/stdc++.h>
using namespace std;
int main() {
    // Андрей выигрывает, только если n = 1, 2 или 9
    // У Стёпы слишком крутые простые числа
    // вот такой вот рофл
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        cout << (n <= 1 || n == 9 ? "Andrey\n" : "Stepan\n");
    }
    return 0;
}
