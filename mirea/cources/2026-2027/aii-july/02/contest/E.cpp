// После чтения массива используем монотонный стек, чтобы для каждого элемента найти
// индекс ближайшего большего слева. Затем, обрабатывая массив справа-налево, находим
// индекс ближайшего большего элемента справа. Суммируем расстояния до найденных
// элементов слева и справа. Чтобы не обрабатывать пустой стек, добавим бесконечность.
#include <bits/stdc++.h>
using namespace std;
const int inf = 1000000007;
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // идём слева-направо и находим расстояние до ближайшего > элемента слева:
    vector<int> answ(n);
    vector<pair<int,int>> st;
    st.push_back({inf, -1});
    for (int i = 0; i < n; i++) {
        while (st.back().first <= a[i])
            st.pop_back();
        answ[i] += (i - st.back().second - 1);
        st.push_back({a[i], i});
    }
    // теперь то же самое, но справа-налево:
    st = {{inf, n}};
    for (int i = n-1; i >= 0; i--) {
        while (st.back().first <= a[i])
            st.pop_back();
        answ[i] += (st.back().second - i - 1);
        st.push_back({a[i], i});
    }
    // выводим ответ:
    for (int i = 0; i < n; i++)
        cout << answ[i] << ' ';
    cout << '\n';
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
