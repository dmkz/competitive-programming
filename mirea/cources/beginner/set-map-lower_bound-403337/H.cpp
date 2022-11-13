#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные:
    int nItems, nQueries;
    cin >> nItems >> nQueries;
    vector<int> a(nItems);
    for (auto &it : a)
        cin >> it;
    // предподсчитываем ответ для каждого суффикса
    // элементы на суффиксе храним в set. используем то, что он хранит
    // только уникальные. тогда set.size() = ответ на запрос
    set<int> st;
    vector<int> answer(nItems);
    for (int i = nItems - 1; i >= 0; i--) {
        st.insert(a[i]);
        answer[i] = (int)st.size();
    }
    // отвечаем на запросы:
    while (nQueries--) {
        int suffStart; cin >> suffStart;
        cout << answer[suffStart-1] << '\n';
    }
}