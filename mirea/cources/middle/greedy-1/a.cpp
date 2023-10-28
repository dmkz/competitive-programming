#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // считаем затраты на каждого клиента как x * a + y * b
    // сортируем вектор затрат и набираем клиентов с мин.
    // затратами пока можем
    int n, d; cin >> n >> d;
    int64_t a, b; cin >> a >> b;
    vector<pair<int64_t,int>> costs(n);
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        costs[i] = {x * a + y * b, i+1};
    }
    sort(all(costs));
    vector<int> answ;
    for (auto [cost, id] : costs) {
        if (d >= cost) {
            d -= cost;
            answ.push_back(id);
        } else break;
    }
    cout << answ.size() << "\n";
    for (auto it : answ)
        cout << it << ' ';
    cout << endl;
}
