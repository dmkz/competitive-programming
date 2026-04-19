// предподсчёт, бинарный поиск в массиве
#include <bits/stdc++.h>
using namespace std;
main() {
    // предподсчитаем все ответы:
    vector<int64_t> a = {0, 1};
    for (int i = 1; i <= 1000000; i++)
        a.push_back(a.back() + 6 * i);
    // ответим на все запросы:
    int t; cin >> t;
    while (t --> 0) {
        // находим нужное t бинарным поиском:
        int64_t n; cin >> n;
        cout << int(lower_bound(a.begin(), a.end(), n) - a.begin()) << '\n';
    }
}
