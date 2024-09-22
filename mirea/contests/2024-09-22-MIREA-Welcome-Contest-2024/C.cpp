#include <bits/stdc++.h>
using namespace std;

// проверка на палиндром
bool isPalindrome(string s) {
    for (int i = 0, j = (int)s.size()-1; i < j; i++, j--)
        if (s[i] != s[j])
            return false;
    return true;
}

// конвертирование строку во время в секундах
int getTime(string s) {
    int h, m;
    int code = sscanf(s.c_str(), "%d:%d", &h, &m);
    assert(code == 2);
    return h * 60 + m;
}

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // сначала нужно найти все палиндромы (их 16 штук):
    vector<int> pals;
    for (int currTime = 0; currTime < 24 * 60; currTime++) {
        char buf[100];
        sprintf(buf, "%02d:%02d", currTime / 60 % 24, currTime % 60);
        if (isPalindrome(buf))
            pals.push_back(currTime);
    }
    // решение задачи:
    int tt; cin >> tt;
    while (tt --> 0) {
        string s, t; cin >> s >> t;
        auto t1 = getTime(s);
        auto t2 = getTime(t);
        if (t2 < t1)
            t2 += 24 * 60;
        // переберём известные нам палиндромы и посчитаем сколько
        // из них входят в наш отрезок [t1, t2]
        int answ = 0;
        for (int currTime : pals) {
            if (currTime < t1)
                currTime += 24 * 60;
            if (currTime <= t2)
                answ++;
        }
        cout << answ << "\n";
    }
}
