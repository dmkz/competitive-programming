#pragma GCC optimize("Ofast")
#include "template.hpp"
#include "debug.hpp"
#include "orderedset.hpp"
#include "fastio.hpp"
int main() {
    FastIO::Reader cin;
    FastIO::Writer cout;
    int n, q; cin >> n >> q;
    OrderedMultiset<int> msi;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        msi.insert(a);
    }
    for (int i = 0; i < q; i++) {
        int k; cin >> k;
        if (k >= 0) msi.insert(k);
        else {
            assert(k < 0);
            k = (-k)-1;
            auto it = msi.find_by_order(k);
            msi.erase(it);
        }
    }
    if(!msi.size()) cout << "0\n";
    else cout << *msi.begin() << '\n';
}
