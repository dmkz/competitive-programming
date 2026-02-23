// перестановки, инверсии, разделяй-и-властвуй
#include <bits/stdc++.h>
using namespace std;
int64_t f(auto &a, int l, int r) {
    if (l + 1 == r)
        return 0;
    // делим отрезок пополам и считаем число инверсий в каждой половине:
    int m = (l+r)/2;
    int64_t res = f(a, l, m) + f(a, m, r);
    // двумя указателями считаем ответ для пар, пересекающих середину:
    int p = m;
    for (int i = l; i < m; i++) {
        while (p < r && a[p] < a[i])
            p++;
        res += p - m;
    }
    // объединяем отсортированные полуинтервалы [l, m) и [m, r):
    inplace_merge(a.begin()+l, a.begin()+m, a.begin()+r);
    return res;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    int64_t answ{};
    for (int i = 0; i < k; i++) {
        vector<int> a(n);
        for (int j = 0; j < n; j++)
            cin >> a[j];
        answ += f(a, 0, n);
    }
    cout << answ << endl;
}
