#include <bits/stdc++.h>
#define int int64_t
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем + сортируем
    int n, k;
    cin >> n >> k;
    set<int> a;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.insert(x);
    }
    if (k == 1) {
        cout << a.size() << endl;
        return 0;
    }
    // теперь мы должны для каждого числа x вычеркнуть x * k 
    for (auto x = a.begin(); x != a.end(); x++)
        if (auto y = a.find(*x * k); y != a.end())
            a.erase(y);
    cout << a.size() << endl;
}
