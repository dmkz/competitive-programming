#include <bits/stdc++.h>

typedef int64_t Int;

using namespace std;

Int sum2(Int v) {
    Int s = 0;
    Int p = 1;
    while (p <= v) {
        s += p;
        p *= 2;
    }
    return s;
}


Int answer(Int v) {
    return v * (v+1) / 2 - 2 * sum2(v);
}


int main() {
//    freopen("input.txt", "rt", stdin);
//    freopen("output.txt", "wt", stdout);
    
    Int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        Int v;
        cin >> v;
        cout << answer(v) << "\n";
    }
    return 0;
}