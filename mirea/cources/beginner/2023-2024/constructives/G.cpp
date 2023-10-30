#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
main() {
    // когда баланс становится отрицательным, надо менять текущую закрываюшую скобку на
    // самую-самую правую открывающую
    string s; cin >> s;
    const int n = (int)s.size();
    int balance = 0, rightOpen = n-1, answ{};
    for (int i = 0; i < n; i++) {
        balance += (s[i] == '(' ? +1 : -1);
        if (balance < 0) {
            // ищем самую правую открывающую с того момента, на котором остановились
            // при последнем поиске:
            while (s[rightOpen] == '(')
                rightOpen--;
            // меняем местами:
            swap(s[i], s[rightOpen]);
            // обновляем скобочный баланс после обмена:
            balance += 2;
            // обновляем ответ:
            answ++;
        }
    }
    cout << answ << endl;
}
