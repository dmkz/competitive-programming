#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
int getbit(int a, int i) {
    return (a >> i) & 1;
}
main() {
    int n; cin >> n;
    vi a(n), b(n), fixed(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int k = 0;
        while ((1 << k) <= a[i])
            k++;
        b[i] = (1 << k) - a[i] - 1;
    }
    int answ{};
    for (int bit = 30; bit >= 0; bit--) {
        // можем ли получить 1 в бите "bit"?
        bool can = true;
        for (int i = 0; can && i < n; i++) {
            if (getbit(a[i], bit) == 0) {
                if (!fixed[i] && getbit(b[i], bit) == 1) {
                    //can = true;
                } else
                    can = false;
            }
        }
        if (!can)
            continue;
        answ |= (1 << bit);
        for (int i = 0; i < n; i++) {
            if (getbit(a[i], bit) == 0) {
                if (!fixed[i] && getbit(b[i], bit) == 1) {
                    swap(a[i], b[i]);
                    fixed[i] = 1;
                }
            } else {
                if (getbit(b[i], bit) == 0)
                    fixed[i] = 1;
            }
        }
    }
    cout << answ << endl;
}
