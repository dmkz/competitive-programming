#include <bits/stdc++.h>
using namespace std;
void solve() {
    // чтение данных
    // нам дан уже посорченный по времени подхода к очереди порядок
    int n; cin >> n;
    int currTime = 0; // время, когда очередь освободится
                      // перед приходом i-го чувака
    while (n --> 0) {
        int L, R; cin >> L >> R;
        if (currTime > R) { // уходит либо уже ушёл раньше
            cout << "0 ";
            continue;
        }
        // определим время, когда он нальёт себе чай:
        currTime = max(currTime, L);
        cout << currTime << " ";
        // наливаем, затрачивая 1 секунду
        currTime++;
    }
    cout << '\n';
}
int main() {
    int nTests; cin >> nTests;
    while (nTests --> 0) solve();
}