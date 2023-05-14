#include <bits/stdc++.h>
using namespace std;
int main() {
    // ускорение ввода-вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем запросы и отвечаем на них:
    int tt; cin >> tt;
    while (tt --> 0) {
        int n, k;
        cin >> n >> k;
        // минимальное число, которое делится, это n * k
        long long min = n * 1LL * k;
        // вместе с минимальным, есть ещё n-1 число, которое даёт k при делении на n
        // до числа min + n не включительно, так как (min+n) / n = k + 1 > k
        long long max = min + n - 1;
        cout << min << ' ' << max << '\n';
    }
    return 0;
}
