#include <bits/stdc++.h>
using namespace std;
main() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &it : a) cin >> it;
    for (auto &it : b) cin >> it;
    sort(b.begin(), b.end());
    int answer = 0;
    for (int ai : a) {
        int minR = INT_MAX;
        // ближайшую вышку справа:
        auto iter = lower_bound(b.begin(), b.end(), ai);
        if (iter != b.end()) minR = min(minR, *iter - ai);
        // ближайшую слева:
        if (iter != b.begin()) minR = min(minR, ai - *(--iter));
        // обновляем ответ:
        answer = max(answer, minR);
    }
    cout << answer << endl;
}
