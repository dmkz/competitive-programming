#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
main() {
    vector<int> a(4);
    for (auto &it : a)
        cin >> it;
    sort(all(a));
    bool ok = false;
    do {
        // Перебираем все перестановки ножек. Разница высот должна быть одинаковая
        // для противоположных сторон
        // a[1] .... a[2]
        // ....      ....
        // a[0] .... a[3]
        int deltaHeight1 = a[1] - a[0];
        int deltaHeight2 = a[2] - a[3];
        int  deltaWidth1 = a[2] - a[1];
        int  deltaWidth2 = a[3] - a[0];
        if (deltaHeight1 == deltaHeight2 && deltaWidth1 == deltaWidth2)
            ok = 1;
    } while (next_permutation(all(a)));
    cout << (ok ? "YES\n" : "NO\n");
}
