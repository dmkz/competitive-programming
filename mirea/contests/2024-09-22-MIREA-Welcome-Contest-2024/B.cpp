#include <bits/stdc++.h>
using namespace std;
/*
    Какую сумму надо считать?
    sum_{i=0}^{len-1} (L + i) * (R - i)
    Раскроем скобки и посчитаем слагаемые отдельно:
    sum_{i=0}^{len-1} (L*R)
    +sum_{i=0}^{len-1} i*(R-L)
    -sum_{i=0}^{len-1} i^2
*/
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // предподсчёт суммы квадратов
    vector<long long> sum2(1e6+100);
    for (int i = 1; i < (int)(sum2.size()); i++)
        sum2[i] = sum2[i-1] + (long long)(i) * i;
    // решение задачи:
    int tt; cin >> tt;
    while (tt --> 0) {
        int L, R; cin >> L >> R;
        int len = R - L + 1;
        long long res = (long long)(L) * R * len;
        res += (long long)(R - L) * len * (len-1)/2;
        res -= sum2[len-1];
        cout << res << "\n";
    }
}
