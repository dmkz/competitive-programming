#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем конечную ступень:
    int n; cin >> n;
    vector<int> path;
    function<void(int)> enumerate = [&](int i) {
        if (i == n) {
            for (auto it : path)
                cout << it << ' ';
            cout << '\n';
            return;
        }
        if (i > n) return;
        // Продолжаем маршрут каждым допустимым прыжком.
        for (int jump : {1, 2}) {
            path.push_back(jump);
            enumerate(i + jump);
            path.pop_back();
        }
    };
    enumerate(0);
}