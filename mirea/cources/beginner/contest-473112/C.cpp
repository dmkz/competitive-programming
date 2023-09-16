#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
void remin(auto &x, const auto &y) { if (y < x) x = y; }
void remax(auto &x, const auto &y) { if (x < y) x = y; }
int main() {
    // читаем данные
    string s; cin >> s;
    // считаем сколько каждой буквы есть
    vi countLetter(26);
    for (auto ch : s)
        countLetter[ch-'a']++;
    // считаем кол-во уникальных букв, минимальное кол-во и максимальное кол-во
    int numLetters = 0, Max = 0, Min = INT_MAX;
    for (int i = 0; i < 26; i++)
        if (countLetter[i] > 0) {
            remax(Max, countLetter[i]);
            remin(Min, countLetter[i]);
            numLetters++;
        }
    // теперь готовы сообщать ответ
    if (numLetters > 4 || numLetters == 1) {
        cout << "No\n";
        return 0;
    }
    if (numLetters == 4) {
        cout << "Yes\n";
        return 0;
    }
    // осталось проверить случай 2 и 3 уник буквы
    if (numLetters == 3) {
        cout << (Max > 1 ? "Yes\n" : "No\n");
        return 0;
    }
    assert(numLetters == 2);
    cout << (Max > 1 && Min > 1 ? "Yes\n" : "No\n");
}
