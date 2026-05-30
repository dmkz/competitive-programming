#include <bits/stdc++.h>
using namespace std;
// тройки: (элемент; его индекс; количество меньших его)
void inversions(auto begin, auto end) {
    if (begin == end || begin + 1 == end)
        return;
    auto mid = begin + (end - begin) / 2;
    inversions(begin, mid);
    inversions(mid, end);
    // что-то делаем с этими половинами
    auto i = begin;
    for (auto j = mid; j < end; j++) {
        // подвинуть указатель i:
        while (i != mid && get<0>(*i) <= get<0>(*j))
            i++;
        get<2>(*j) += (mid - i);
    }
    // слить две отсортированные половины:
    inplace_merge(begin, mid, end);
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<tuple<int, int, int>> p(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        p[i] = {x, i, 0};
    }
    inversions(p.begin(), p.end());
    // выводим ответ:
    vector<int> answer(n);
    for (const auto &[x, i, cntI] : p)
        answer[i] = cntI;
    for (int i = 0; i < n; i++)
        cout << answer[i] << ' ';
    cout << '\n';
}