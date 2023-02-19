#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, p, q;
    cin >> n >> p >> q;
    string s; cin >> s;
    // np - число строк длины p
    // nq - число строк длины q
    // переберём все варианты и проверим каждый вариант
    for (int np = 0; np <= n / p; np++)
        for (int nq = 0; nq <= (n - p * np) / q; nq++) {
            if (np * p + nq * q == n) {
                cout << np + nq << '\n';
                // сначала выводим построки длины p, удаляя их:
                for (int i = 0; i < np; i++) {
                    cout << s.substr(0, p) << '\n';
                    s = s.substr(p);
                }
                // теперь выводим построки длины q, удаляя их:
                for (int i = 0; i < nq; i++) {
                    cout << s.substr(0, q) << '\n';
                    s = s.substr(q);
                }
                return 0;
            }
        }
    cout << "-1\n";
}