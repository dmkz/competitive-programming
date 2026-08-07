#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем уже отсортированный массив и число, для которого ищем границу.
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int x; cin >> x;
    // low точно не подходит, high точно подходит как служебная позиция n.
    int low = -1, high = n;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (a[mid] >= x) high = mid;
        else low = mid;
    }
    cout << high << '\n';
}