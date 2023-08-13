#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем исходные данные:
    int n, k; cin >> n >> k;
    string s; cin >> s;
    // используем то, что надо построить любой подходящий ответ
    // тогда можно набирать жадно максимальное расстояние для каждого символа
    // пока k не закончится
    string t(n, '?');
    for (int i = 0; i < n; ++i) {
        int left = s[i] - 'a'; // расстояние по направлению уменьшения буквы
        int right = 'z' - s[i];// расстояние по направлению увеличения буквы
        if (left < right) {
            // до 'z' дальше, чем до 'a'
            int delta = min(k, right);
            t[i] = s[i] + delta;
            k -= delta;
        } else {
            // до 'a' дальше, чем до 'z'
            int delta = min(k, left);
            t[i] = s[i] - delta;
            k -= delta;
        }
    }
    // выводим ответ (если k не кончилось, то -1):
    cout << (k > 0 ? "-1" : t);
    return 0;
}