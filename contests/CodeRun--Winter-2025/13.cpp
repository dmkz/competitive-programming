#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
void solve() {
    int n; std::cin >> n;
    vi p(n);
    for (auto &it : p)
        std::cin >> it;
    std::set<int> elem;
    for (int i = 1; i <= n; i++)
        elem.insert(i);
    const int undef = n+1;
    elem.insert(undef);
    // 3 2 1 4
    // 1 3 2 4
    vi a(n);
    for (int i = 0; i < n; i++) {
        if (auto it = elem.find(p[i]); it != elem.end()) {
            elem.erase(it);
            a[i] = *elem.begin();
            elem.erase(elem.begin());
            elem.insert(p[i]);
        } else {
            a[i] = *elem.begin();
            elem.erase(elem.begin());
        }
    }
    for (int i = 0; i + 1 < n; i++)
        assert(a[i] != p[i]);
    if (a.back() == undef) {
        assert(isz(elem) && *elem.begin() == n);
        bool was = false;
        for (int j = 0; j + 1 < n; j++)
            if (a[j] == n-1) {
                a[j] = n;
                a.back() = n-1;
                was = true;
                break;
            }
        assert(was);
    }
    for (auto it : a) std::cout << it << ' ';
    std::cout << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; //std::cin >> tt;
    while (tt --> 0) solve();
}
