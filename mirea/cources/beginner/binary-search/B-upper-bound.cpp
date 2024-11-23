#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    // читаем вектор и сортируем его:
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    sort(a.begin(), a.end());
    // читаем запросы и отвечаем на них
    for (int j = 0, bj; j < m; j++) {
        cin >> bj;
        cout << upper_bound(a.begin(), a.end(), bj) - a.begin() << " ";
    }
    // первый больший - upper_bound => кол-во меньше либо равных UB - begin
    // первый >= - LB => кол-во меньших LB - begin
    // equal_range = [LB, UB] => кол-во равных UB - LB
    // binary_search -> true, если элемент есть, и false, если элемента нет
}
