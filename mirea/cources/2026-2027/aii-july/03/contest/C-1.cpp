// храним одновременно и stack, и map. Минимум, максимум и количество уникальных
// берём из map, а при удалении вынимаем значение из stack, уменьшаем его количество и,
// если оно стало равно нулю, удаляем его из map.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные
    int n; cin >> n;
    map<int, int> cnt;
    stack<int> st;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        st.push(x);
        cnt[x]++;
    }
    // обрабатываем запросы
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == '+') {
            int x; cin >> x;
            st.push(x);
            cnt[x]++;
        } else if (c == '?') {
            int Min = cnt.begin()->first;
            int Max = cnt.rbegin()->first;
            int Cnt = cnt.size();
            cout << Min << ' ' << Max << ' ' << Cnt << '\n';
        } else if (c == '-') {
            // сначала удалим из стека:
            int last = st.top();
            st.pop();
            // теперь аккуратно удалим из map:
            auto iter = cnt.find(last);
            iter->second--; // уменьшаем количество
            if (iter->second == 0) // стало равным нулю => удаляем
                cnt.erase(iter);
        }
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
