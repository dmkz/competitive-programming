#include <bits/stdc++.h>
using namespace std;
int solve(const string &s) {
// эта функция считает кол-во способов заменить открывающую скобку закрывающей
// для этого суммарный скобочный баланс должен быть равен +2
// считаем баланс на каждом префиксе:
    int n = (int)s.size();
    vector<int> pref(1+n, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + (s[i-1] == '(' ? +1 : -1);
        if (pref[i] < 0)
            return 0;
    }
// суммарный баланс должен быть равен 2, иначе замена на поможет:
    if (pref[n] != 2)
        return 0;
// теперь считаем минимальный префиксный баланс на каждом суффиксе
// и проверяем критерий замены: минимум на суффиксе >= 2
    int answ = 0, suffMin = pref[n];
    for (int i = n; i >= 1; --i) {
        suffMin = min(pref[i], suffMin);
        answ += (s[i-1] == '(' && suffMin >= 2);
    }
    return answ;
}
// чтобы не рассматривать два случая, вводим функцию разворота скобочной
// последовательности, чтобы использовать тот же самый код
string reverseBracketSequence(string s) {
    reverse(s.begin(), s.end());
    for (char &c : s)
        c = (c == '(' ? ')' : '(');
    return s;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    cout << solve(s) + solve(reverseBracketSequence(s)) << '\n';
    return 0;
}
