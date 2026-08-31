#include <bits/stdc++.h>
using namespace std;
void solve() {
    int64_t r; cin >> r;
    std::vector<int64_t> fib={1,1};
    for (int i = 2; fib[i-2] + fib[i-1] <= r; i++)
        fib.push_back(fib[i-2] + fib[i-1]);
    cout << *(fib.end()-1) << ' ' << *(fib.end()-2) << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}
