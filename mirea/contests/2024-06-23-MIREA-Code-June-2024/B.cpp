#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        string s; cin >> s;
        // можно было пробежаться по строке, посчитать кол-во минусов,
        // заодно найти цифры и записать их куда-нибудь, но я решил обработать
        // это как правильную скобочную последовательность зачем-то
        deque<char> d(all(s));
        int sign = 1;
        while (true) {
            if (d.size() && d[0] == '-') {
                // удаляем минус из начала дэка
                d.pop_front();
                sign *= -1;
            } else if (d.size() >= 2 && d.front() == '(' && d.back() == ')') {
                // удаляем скобочки ( и ) с концов дэка
                d.pop_front();
                d.pop_back();
            } else {
                // на краях ни минуса, ни скобочек нет, значит осталось лишь число
                break;
            }
        }
        // выводим число умноженное на его знак
        s.assign(all(d));
        cout << sign * stoi(s) << "\n";
    }
}