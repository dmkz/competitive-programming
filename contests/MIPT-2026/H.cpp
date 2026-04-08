// математика, формулы, целочисленное деление
#include <bits/stdc++.h>
using namespace std;
main() {
    int p, h, t;
    cin >> p >> h >> t;
    if (h <= p) {
        // успевают развешивать плакаты до появления нового:
        int k = t / p; // k плакатов распечатаны
        if (k == 0) {
            cout << 0 << endl;
        } else {
            int answ = k-1; // (k-1) точно развешены
            int lastPrinted = k * p;
            if (lastPrinted + h <= t)
                answ++; // успеваем повесить последний плакат
            cout << answ << endl;
        }
    } else {
        // вешают дольше, чем печатают:
        cout << max(0, (t - p) / h) << endl;
    }
}
