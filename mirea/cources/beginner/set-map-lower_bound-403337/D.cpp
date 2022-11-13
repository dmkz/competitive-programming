#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем общежития + считаем префикс-суммы:
    int nHouses, nQueries;
    cin >> nHouses >> nQueries;
    vector<int64_t> a(1+nHouses);
    for (int i = 1; i <= nHouses; i++) {
        cin >> a[i];
        a[i] += a[i-1];
    }
    // отвечаем на запросы:
    while(nQueries--) {
        int64_t x; cin >> x;
        // надо найти первый элемент, который >= x
        int houseIndex = lower_bound(all(a), x) - a.begin();
        cout << houseIndex << ' ' << (x - a[houseIndex-1]) << '\n';
    }
}