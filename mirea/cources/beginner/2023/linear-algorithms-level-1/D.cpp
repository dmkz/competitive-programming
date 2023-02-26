#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // после сортировки надо посчитать минимум среди разностей
    // соседних элементов вектора и его количество
    sort(a.begin(), a.end());
    int min = (a[1] - a[0]), cnt = 1;
    for (int i = 2; i < n; i++) {
        int diff = (a[i] - a[i-1]);
        if (diff < min) min = diff, cnt = 1;
        else if (diff == min) cnt++;
    }
    cout << min << ' ' << cnt << '\n';
}