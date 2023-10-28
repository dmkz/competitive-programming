#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // рассмотрим случай n = 2, выведем компаратор - кого лучше брать, и посортим
    // всех драконов по этому компаратору
    // порядок ij, понадобится max(ai, aj + bi) солдат
    // порядок ji, понадобится max(aj, ai + bj) солдат
    int n; cin >> n;
    vector<pair<int,int>> arr(n);
    for (auto &[a,b] : arr)
        cin >> a >> b;
    sort(all(arr), [](const auto &lhs, const auto &rhs) {
        auto [ai,bi] = lhs;
        auto [aj,bj] = rhs;
        return max(ai, aj + bi) < max(aj, ai + bj);
    });
    // теперь проще всего написать бинпоиск и убивать солдат в выгодном порядке
    int64_t low = -1, high = 1e18L;
    while (high - low > 1) {
        const int64_t mid = (low + high) / 2;
        // проверяем достаточно ли текущего количества солдат
        int64_t army = mid;
        bool ok = 1;
        for (const auto &[a,b] : arr) {
            if (army >= a)
                army -= b;
            else {
                ok = false;
                break;
            }
        }
        if (ok) high = mid;
        else low = mid;
    }
    cout << high << endl;
}
