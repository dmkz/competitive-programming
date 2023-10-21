#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // нужно знать лишь текущее время, когда человек освободится, посмотрев все
    // накопленные видео. Если оно меньше времени, когда приходит новое видео, то
    // мы вынуждены ждать, иначе добавляем длину нового видео к этому времени
    int n; cin >> n;
    int64_t currT = 0;
    for (int i = 0; i < n; i++) {
        int t, d;
        cin >> t >> d;
        if (t >= currT)
            currT = t;
        currT += d;
    }
    cout << currT << endl;
}
