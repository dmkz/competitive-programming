#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n, k; cin >> n >> k;
        vector<int> a(k);
        for (auto &it : a)
            cin >> it;
        // ответ это просто n-k, но важно не скипать чтение
        // номеров в мультитестах
        cout << n - k << endl;
    }
}