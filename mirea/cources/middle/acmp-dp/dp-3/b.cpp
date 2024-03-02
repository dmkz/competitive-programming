#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
// будем использовать 128-битный целый тип и напишем для него оператор вывода
using Int = __int128;
std::ostream &operator<<(std::ostream &os, Int number) {
    if (number < 0) {
        // выводим знак
        os << '-';
        number *= -1;
    }
    string digits;
    do {
        digits += char('0' + number % 10);
        number /= 10;
    } while (number > 0);
    reverse(all(digits));
    return os << digits;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    // dp[k][d] = число номеров длины k, оканчивающихся цифрой d
    vector dp(n+1, vector<Int>(10, 0));
    // инициализация динамики
    for (int startDigit : {1, 2, 3, 4, 5, 6, 7, 9})
        dp[1][startDigit] = 1;
    // переходы
    vector<vector<int>> from = {
        {4, 6},    // в цифру 0
        {8, 6},    // в цифру 1
        {7, 7},    // в цифру 2
        {4, 8},    // в цифру 3
        {3, 9, 0}, // в цифру 4
        {},        // в цифру 5
        {1, 7, 0}, // в цифру 6
        {2, 6},    // в цифру 7
        {1, 3},    // в цифру 8
        {2, 4}     // в цифру 9
    };
    for (int len = 2; len <= n; len++)
        for (int digit = 0; digit <= 9; digit++)
            for (int prev : from[digit])
                dp[len][digit] += dp[len-1][prev];
    cout << accumulate(all(dp[n]), Int(0)) << endl;
}
