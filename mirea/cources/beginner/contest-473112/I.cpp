#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using vi = vector<int>;

ld solve(int n, const vi &a) {
    map<int, int> count;
    ld sum = 0;
    for (int item : a) {
        count[item]++;
        sum += item;
    }
    ld answ = 0;
    for (int item : a) {
        // удаляем текущий элемент
        n--;
        count[item]--;
        sum -= item;
        // считаем сумму разностей со всеми остальными элементами
        ld excludedCount = 0, excludedSum = 0;
        for (int delta : {-1,0,1}) {
            excludedCount += count[item+delta];
            excludedSum += ld(item+delta) * count[item+delta];
        }
        answ += (sum - excludedSum) - (n - excludedCount) * item;
    }
    return (ld)answ;
}
int main() {
    int n; cin >> n;
    vi a(n); for (auto &it : a) cin >> it;
    cout << fixed << setprecision(0);
    cout << solve(n, a) << endl;
}
