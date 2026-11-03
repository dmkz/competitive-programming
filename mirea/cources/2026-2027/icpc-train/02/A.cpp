#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
// функция для перевода из строки формата "HH:MM:SS" в секунды:
int time2sec(const auto &s) {
    int hh, mm, ss;
    int code = sscanf(s.c_str(), "%d:%d:%d", &hh, &mm, &ss);
    assert(code == 3);
    return ss + 60 * (mm + hh * 60);
}
// функция для перевода из секунд в строку формата "HH:MM:SS":
string sec2time(int ss) {
    int hh = ss / 3600;
    int mm = ss / 60 % 60;
    ss %= 60;
    char buf[101];
    sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
    return buf;
}
// решение задачи:
void solve() {
    int q; cin >> q;
    // храним для каждого чувака его последнее известное состояние (вышел/вошёл, время в секундах):
    map<string, pair<string,int>> cache;
    // а здесь храним ответ в секундах для каждого:
    map<string, int> answ;
    while (q --> 0) {
        string sTime, sName, sType;
        cin >> sTime >> sName >> sType;
        int sec = time2sec(sTime);
        // смотрим, что делал человек до этого, и обновляем ответ и его состояние
        if (sType == "OUT") {
            auto it = cache.find(sName);
            if (it == cache.end())
                // не было, но ушёл
                answ[sName] += sec;
            else
                answ[sName] += sec - it->second.second;
            cache[sName] = {"OUT", sec};
        } else if (sType == "IN") {
            auto it = cache.find(sName);
            if (it != cache.end() && it->second.first == "IN") {
                // ничего не делаем, он повторно приложил пропуск
            } else
                cache[sName] = {"IN", sec};
        }
    }
    // все те, кто до сих пор внутри, должны выйти: обновляем для них ответ:
    for (const auto &[name, val] : cache)
        if (val.first == "IN")
            answ[name] += 24*60*60 - val.second;
    // выводим ответ:
    for (const auto &[name, sec] : answ)
        cout << name << ' ' << sec2time(sec) << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0) solve();
    return 0;
}