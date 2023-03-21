#include <bits/stdc++.h>
using namespace std;
bool isLeapYear(int y) {
// високосный год или нет
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}
int daysInYear(int y) {
    return 365 + isLeapYear(y);
}
int main() {
    int y; cin >> y;
    // надо найти первый год, до первого дня которого прошло
    // кратное 7 число дней, а високосность бы совпала с данным годом
    int days = daysInYear(y);
    int answer = y + 1;
    while (!(isLeapYear(answer) == isLeapYear(y) && days % 7 == 0)) {
        days += daysInYear(answer);
        answer++;
    }
    cout << answer << '\n';
}
