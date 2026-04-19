// перестановки, циклы, O(n)
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; int64_t k;
        cin >> n >> k;
        vector<int> perm(n);
        for (int i = 0; i < n; i++)
            cin >> perm[i], perm[i]--;
        // раскладываем перестановку в произведение независимых циклов:
        vector<int> used(n), cycle, answ(n);
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                // ищем цикл, который начинается с элемента i:
                used[i] = 1;
                cycle = {i};
                for (int j = perm[i]; j != i; j = perm[j]) {
                    used[j] = 1;
                    cycle.push_back(j);
                }
                // сдвигаем все элементы цикла на k mod (длина цикла)
                for (int j = 0; j < (int)cycle.size(); j++)
                    answ[cycle[j]] = cycle[(j + k) % (int)cycle.size()];
            }
        }
        // выводим ответ:
        for (int i = 0; i < n; i++)
            cout << (answ[i] + 1) << ' ';
        cout << '\n';
    }
}
