#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()

using namespace std;
using vi = vector<int>;

vi tryToErase(vi s, int count, int digit1, int digit2, int digit3) {
// s - исходная строка
// count - количество символов, которое нужно вычеркнуть, чтобы сумма
// цифр начала делиться на 3
// digit1, digit2 и digit3 - цифры, которые мы пытаемся вычеркнуть
    auto needToErase = [&](int c) {
        return c == digit1 || c == digit2 || c == digit3;
    };
    // начинаем вычеркивать с правого конца числа
    int pos = isz(s)-1;
    while (count > 0) {
        while (pos >= 0 && !needToErase(s[pos])) --pos;
        if (pos < 0) break;
        // надо вычеркнуть s[pos]
        --count;
        s.erase(s.begin() + pos);
        --pos;
    }
    // удаляем лидирующие нули
    int zeroPrefix = 0;
    while (zeroPrefix < isz(s) && s[zeroPrefix] == 0) ++zeroPrefix;
    s.erase(s.begin(), s.begin()+zeroPrefix);
    // возвращаем ответ
    if (count > 0) // не удалось вычеркнуть нужное кол-во символов
        return {};
    // число состояло целиком из лидирующих нулей после вычёркивания
    if (zeroPrefix > 0 && s.empty())
        s = {0};
    return s;
}

// каждый раз вычитать '0' не удобно, поэтому вычтем заранее и будем
// работать с вектором из интов (от 0 до 9)
vi stringToVector(string s) {
    vi res(isz(s));
    for (int i = 0; i < isz(s); i++)
        res[i] = s[i] - '0';
    return res;
}

string vectorToString(vi a) {
    string s;
    for (int i = 0; i < isz(a); i++)
        s += char('0' + a[i]);
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vi s;
    {
        string inputString; cin >> inputString;
        // вычитаем '0' из каждого символа, чтобы работать с числами
        s = stringToVector(inputString);
    }
    // сумма цифр
    int sum = accumulate(all(s),0);
    if (sum % 3 == 0) {
        // ничего вычетать не надо
        cout << vectorToString(s);
        return 0;
    }
    // в зависимости от остатка от деления суммы на 3, смотрим, что выгоднее
    // зачеркнуть. Для любого остатка есть только два варианта оптимального
    // вычёркивания из строки
    vi t1, t2;
    if (sum % 3 == 1) { // либо одну цифру 1, 4, 7, либо две цифры 2, 5, 8
        t1 = tryToErase(s, 1, 1, 4, 7);
        t2 = tryToErase(s, 2, 2, 5, 8);
    } else { // либо две цифры 1, 4, 7, либо одну цифру 2, 5, 7
        t1 = tryToErase(s, 2, 1, 4, 7);
        t2 = tryToErase(s, 1, 2, 5, 8);
    }
    // выводим ответ. функция вернёт пустой вектор, если не возможно
    if (t1.empty() && t2.empty())  cout << "-1\n";
    else if (t1.empty()) cout << vectorToString(t2) << "\n";
    else if (t2.empty()) cout << vectorToString(t1) << "\n";
    else cout << vectorToString((t1.size() < t2.size() ? t2 : t1)) << "\n";
    return 0;
}
