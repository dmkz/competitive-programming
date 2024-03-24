#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
bool isPalindromeTime(int currTime) {
    int mm = currTime % 60;
    int hh = currTime / 60 % 24;
    char buf[100];
    sprintf(buf, "%02d:%02d", hh, mm);
    // строка в прямом порядке:
    string direct = buf;
    // строка в обратном порядке:
    string reversed = direct;
    reverse(all(reversed));
    // проверка на палиндром:
    return (direct == reversed);
}
void solve() {
    string s;
    getline(cin, s);
    // читаем время и период
    int hh, mm, x; char temp;
    cin >> hh >> temp >> mm >> x;
    //cout << hh << ":" << mm << " " << x << endl;
    int currTime = mm + 60 * hh;
    // начинаем считать в цикле, пока не придём в уже посещённое время
    vector<bool> visited(24 * 60);
    int answer = 0;
    while (!visited[currTime]) {
        // проверяем текущее время на палиндром:
        answer += isPalindromeTime(currTime);
        // отмечаем посещённым:
        visited[currTime] = true;
        // сдвигаем время на x:
        currTime += x;
        currTime %= (24 * 60);
    }
    cout << answer << "\n";
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
