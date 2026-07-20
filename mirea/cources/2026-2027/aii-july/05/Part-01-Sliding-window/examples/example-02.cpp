// Пример: минимум в каждом окне длины k через мультимножество.
// Ввод: n, k и массив a.
// Вывод: минимумы всех окон длины k слева направо.

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    multiset<int> st;
    // Загружаем в мультимножество первое окно целиком.
    for (int i = 0; i < k; i++) {
        st.insert(a[i]);
    }

    for (int left = 0; left + k <= n; left++) {
        if (left > 0) {
            cout << ' ';
        }
        cout << *st.begin();

        if (left + k < n) {
            // Удаляем элемент, который вышел из окна, и добавляем новый.
            st.erase(st.find(a[left]));
            st.insert(a[left + k]);
        }
    }
    cout << '\n';

    return 0;
}