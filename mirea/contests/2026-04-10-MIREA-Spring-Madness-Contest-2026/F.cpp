// строки, реализация, максимальный общий префикс и суффикс, O(n^2)
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        string s, t;
        cin >> s >> t;
        if (s.find(t) != s.npos) {
            cout << "0\n0\n";
            continue;
        }
        // строка s входит в строку t: префикс и суффикс определяются однозначно
        if (size_t pos = t.find(s); pos != t.npos) {
            string pref = t.substr(0, pos);
            string suff = t.substr(pos + s.size());
            reverse(pref.begin(), pref.end());
            cout << pref.size() << ' ' << pref << '\n';
            cout << suff.size() << ' ' << suff << '\n';
            continue;
        }
        // иначе мы вставляем либо только в конец, либо только в начало
        // ищем наибольший суффикс s, совпадающий с префиксом t:
        int maxPref = 0, maxSuff = 0;
        for (int len = 0; len <= (int)min(s.size(), t.size()); len++)
            if (s.substr((int)s.size()-len) == t.substr(0, len))
                maxSuff = len;
        // ищем наибольший префикс s, совпадающий с суффиксом t:
        for (int len = 0; len <= (int)min(s.size(), t.size()); len++)
            if (s.substr(0, len) == t.substr((int)t.size() - len, len))
                maxPref = len;
        // выводим ответ:
        if (maxPref >= maxSuff) {
            // вставляем только в префикс:
            t.resize((int)t.size() - maxPref);
            reverse(t.begin(), t.end());
            cout << t.size() << ' ' << t << "\n0\n";
        } else {
            // вставляем только в суффикс:
            t = t.substr(maxSuff);
            cout << "0\n" << t.size() << ' ' << t << '\n';
        }
    }
}
