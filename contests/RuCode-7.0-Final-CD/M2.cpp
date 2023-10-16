#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
int main() {
    int l, r; cin >> l >> r;
    vector<int> a;
    for (int x = r; x >= l; x--)
        a.push_back(x);
    
    while (isz(a) > 1) {
        // каждый раз будем выбирать минимум и считать полусумму со вторым
        // минимумом такой же чётности
        bool ok = false;
        for (int i = isz(a)-2; i >= 0; i--) {
            if (a[i] % 2 == a.back() % 2) {
                a.back() = (a[i]+a.back())/2;
                a.erase(a.begin()+i);
                for (int j = isz(a)-2; j >= 0 && a[j] < a[j+1]; j--)
                    swap(a[j], a[j+1]);
                ok = 1;
                break;
            }
        }
        if (!ok) {
            cout << -1 << endl;
            return 0;
        }
    }
    cout << a[0] << endl;
}
