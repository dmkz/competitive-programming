#include <bits/stdc++.h>

#define all(x) (x).begin(),(x).end()
#define int ll

using namespace std;
using ll = long long;
using vi = vector<int>;

bool check(const vi &a, const vi &b, int r) {
    // проверить что все деревни покрыты
    // можем вставить деревни в set и вырезать из него
    // целый отрезок
    set<int> s(all(a));
    for (const auto &center : b)
        s.erase(s.lower_bound(center-r),
                s.upper_bound(center+r));
    return s.empty();
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение
    int n, m;
    cin >> n >> m;
    vi a(n), b(m);
    for (auto &it : a)
        cin >> it;
    for (auto &it : b)
        cin >> it;
    // сортировка
    sort(all(a));
    sort(all(b));
    // бинпоиск по ответу
    // ответ может лежать в диапазоне [0, 2*10^9]
    // поэтому low = -1, high = 2*10^9+1
    int low = -1, high = (int)2e9+1;
    // инвариант: low подходит, high не подходит
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (check(a,b,mid)) high = mid;
        else low = mid;
    }
    cout << high << endl;
}
