#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    // читаем вектор и сортируем его:
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    sort(a.begin(), a.end());
    // читаем запросы и отвечаем на них
    for (int j = 0, bj; j < m; j++) {
        cin >> bj;
        int low = -1, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (a[mid] <= bj) low = mid;
            else high = mid;
        }
        cout << high << " ";
    }
}
