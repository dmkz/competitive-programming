#include <bits/stdc++.h>
using namespace std;
// [l; r] -> [l; r+1)

struct Fenwick {
    
    vector<int64_t> data;
    
    Fenwick(int n) : data(n) { }
    
    void inc(int i, int x) {
        for (; i < (int)data.size(); i |= i + 1)
            data[i] += x;
    }
    
    int64_t sum(int r) {
        int64_t res = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            res += data[r];
        return res;
    }
    
    int64_t sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
    
};

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    Fenwick fenw(n+1);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        fenw.inc(i  , +ai);
        fenw.inc(i+1, -ai);
    }
    int q; cin >> q;
    while (q --> 0) {
        char ch; cin >> ch;
        if (ch == 'a') {
            int l, r, x; cin >> l >> r >> x;
            l--, r--;
            fenw.inc(l  , +x);
            fenw.inc(r+1, -x);
        } else {
            assert(ch == 'g');
            int pos; cin >> pos;
            pos--;
            cout << fenw.sum(pos) << '\n';
        }
    }
}
