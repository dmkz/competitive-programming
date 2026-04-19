// префиксные суммы, O(n+q)
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    // храним префикс-суммы для элементов, добавленных в конец, и для
    // элементов, добавленных в начало, отдельно. Тогда запрос заспадается
    // на два запроса в двух префикс-суммах.
    vector<int64_t> prefSums1 = {0}, prefSums2 = {0};
    auto push_back = [&](int x) {
        prefSums1.push_back(prefSums1.back() + x);
    };
    auto push_front = [&](int x) {
        prefSums2.push_back(prefSums2.back() + x);
    };
    auto answer_back = [&](int l, int r) {
        return l > r ? 0 : prefSums1[r+1] - prefSums1[l];
    };
    auto answer_front = [&](int l, int r) {
        return l > r ? 0 : prefSums2[r+1] - prefSums2[l];
    };
    auto answer = [&](int l, int r) {
        int addedInFront = (int)prefSums2.size() - 1;
        l -= addedInFront, r -= addedInFront;
        if (r < 0) return answer_front(-r-1, -l-1);
        else if (l >= 0) return answer_back(l, r);
        else return answer_front(0, -l-1) + answer_back(0, r);
    };
    // читаем элементы и добавляем их в конец:
    while (n --> 0) {
        int x; cin >> x;
        push_back(x);
    }
    // обрабатываем запросы:
    while (q --> 0) {
        char c; cin >> c;
        if (c == '?') {
            int l, r; cin >> l >> r;
            cout << answer(l, r) << '\n';
        } else if (c == '>') {
            int x; cin >> x;
            push_front(x);
        } else {
            assert(c == '<');
            int x; cin >> x;
            push_back(x);
        }
    }
}
