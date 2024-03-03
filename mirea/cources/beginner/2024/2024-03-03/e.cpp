#include <bits/stdc++.h>
using namespace std;
void solve() {
    // чтение данных в двунаправленную очередь:
    int n; cin >> n;
    deque<int> candies(n);
    for (auto &it : candies)
        cin >> it;
    // процесс поедания конфет:
    int a = 0, b = 0, steps = 0, prevA = 0, prevB = 0;
    while (candies.size()) {
        // Алиса ест больше, чем Боб
        int curr = 0;
        while (curr <= prevB && !candies.empty()) {
            curr += candies.front();
            candies.pop_front();
        }
        a += curr;
        steps++;
        prevA = curr;
        // Боб ест больше, чем Алиса (если есть, что поесть)
        if (!candies.empty()) {
            curr = 0;
            while (curr <= prevA && !candies.empty()) {
                curr += candies.back();
                candies.pop_back();
            }
            b += curr;
            steps++;
            prevB = curr;
        }
    }
    // выводим ответ:
    cout << steps << " " << a << " " << b << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
