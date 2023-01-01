#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        // Андрей выигрывает, только если n < 2 или n == 9
        cout << (n < 2 || n == 9 ? "Andrey" : "Stepan") << '\n';
    }
}