#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(9);
    // чтобы знать среднее, нам нужно поддерживать значения суммы и количества
    // чисел в нашем множестве. Тогда average = sum / cnt
    // будьте внимательный с выводом вещественных чисел
    // осторожнее c делением на ноль! (когда cnt = 0)
    int n; cin >> n;
    int64_t sum = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        char c; int x;
        cin >> c >> x;
        if (c == '+') {
            sum += x;
            cnt++;
        } else {
            assert(c == '-');
            cnt--;
            sum -= x;
        }
        long double average = sum * 1.0L / cnt;
        cout << (cnt == 0 ? 0 : average) << "\n";
    }
        
}
