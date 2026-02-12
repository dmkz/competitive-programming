// рекурсия, перебор
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
using ld = long double;
using vd = vector<ld>;
using vi = vector<int>;

bool solve(vector<ld> cc, ld target) {
    if (cc.size() == 1u)
        return std::abs(std::abs(cc.front() - target) <= 0.01);
    // переберём резисторы i и j, которые мы соединим:
    for (int i = 0; i < isz(cc); i++)
        for (int j = i + 1; j < isz(cc); j++) {
            ld cNew1 = (cc[i] * cc[j]) / (cc[i] + cc[j]);
            ld cNew2 = cc[i] + cc[j];
            auto ccc = cc;
            ccc.erase(ccc.begin()+j);
            // проверяем параллельное соединение:
            ccc[i] = cNew1;
            if (solve(ccc, target))
                return true;
            // проверяем последовательное соединение:
            ccc[i] = cNew2;
            if (solve(ccc, target))
                return true;
        }
    return false;
}
main() {
    // читаем данные
    int n; cin >> n;
    ld target; cin >> target;
    vector<ld> cc(n);
    for (int i = 0; i < n; i++)
        cin >> cc[i];
    // перебираем подмножества конденсаторов, которые будем использовать
    bool ok = false;
    for (int mask = 1; mask < (1 << n); mask++) {
        vector<ld> c;
        for (int i = 0; i < isz(cc); i++)
            if ((mask >> i) & 1)
                c.push_back(cc[i]);
        ok |= solve(c, target);
    }
    cout << (ok ? "YES\n" : "NO\n");
    
}
