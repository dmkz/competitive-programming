// перестановки, следующая лексикографически
#include <bits/stdc++.h>
using namespace std;
main() {
    int n; cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    bool ok = next_permutation(p.begin(), p.end());
    if (!ok)
        for (int i = 0; i < n; i++)
            p[i] = i+1;
    for (auto it : p)
        cout << it << ' ';
    cout << endl;
}
