#include <bits/stdc++.h>
using namespace std;
void removeLeadingAndTrailingZeros(string &s) {
    // удалим нули с конца и с начала строки, дважды ревёрснув между удалениями с конца (2-й пример)
    for (int reversed = 0; reversed < 2; reversed++) {
        while (!s.empty() && s.back() == '0')
            s.pop_back();
        reverse(s.begin(), s.end());
    }
}
int main() {
    // по условию s > 0, то есть, точно существует ненулевая цифра
    string s; cin >> s;
    // если нет точки, то надо бы добавить в конец (1-й пример)
    if (s.find('.') == s.npos)
        s += '.';
    removeLeadingAndTrailingZeros(s);
    // Точка должна стоять после первой ненулевой цифры
    // Прямо сейчас возможны два случая:
    int b = 0;
    if (s.front() == '.') {
        // первый символ точка, тогда надо перемещать её вправо, пока не свапнем с ненулевой цифрой
        // экспонента уменьшается от каждого перемещения
        int p = 0; // позиция точки
        while (true) {
            swap(s[p],s[p+1]);
            b--;
            if ('1' <= s[p] && s[p] <= '9')
                break;
            else p++;
        }
    } else {
        // иначе первый символ ненулевая цифра
        // точка должна находиться сразу за ним
        for (int p = s.find('.'); p > 1; p--) {
            swap(s[p-1],s[p]);
            b++;
        }
    }
    // выводим ответ:
    removeLeadingAndTrailingZeros(s); // на всякий случай
    // если точка на конце, можем удалить её (3-й пример)
    if (s.find('.') == s.size()-1u)
        s.resize(s.size()-1u);
    if (b == 0) cout << s << '\n';
    else cout << s << "E" << b << '\n';
}