#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
bool is_safe(const vector<int> &a) {
    // считаем разности соседей
    vector<int> diff;
    for (int i = 1; i < isz(a); i++)
        diff.push_back(a[i] - a[i-1]);
    // проверим что все одного знака:
    int sum = accumulate(all(diff), 0);
    int sumAbs = 0;
    int mx = 0, mn = 4;
    for (auto it : diff) {
        sumAbs += abs(it);
        mx = max(mx, abs(it));
        mn = min(mn, abs(it));
    }
    bool ok = (abs(sum) == sumAbs); // все разности одного знака
    ok &= (mn >= 1 && mx <= 3); // все разности в заданном диапазоне
    return ok;
}
void part1() {
    int answ{};
    string s;
    while (getline(cin, s)) {
        // прочитали строку, конвертим в вектор из чисел:
        istringstream is(s);
        vector<int> a;
        for (int x; is >> x; a.push_back(x));
        // прочитали числа
        answ += is_safe(a);
    }
    cout << answ << endl;
}
void part2() {
    int answ{};
    string s;
    while (getline(cin, s)) {
        // прочитали строку, конвертим в вектор из чисел:
        istringstream is(s);
        vector<int> a;
        for (int x; is >> x; a.push_back(x));
        // прочитали числа
        bool ok = 0;
        for (int i = 0; i < isz(a); i++) {
            int b = a[i];
            a.erase(a.begin()+i); // удолили
            ok |= is_safe(a); // проверили
            a.insert(a.begin()+i, b); // вернули обратно
        }
        answ += ok;
    }
    cout << answ << endl;
}
main() {
    part2();
}
