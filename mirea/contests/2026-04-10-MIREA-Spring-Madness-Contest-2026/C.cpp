// жадные алгоритмы, сортировка
#include <bits/stdc++.h>
using namespace std;
main() {
    int t; cin >> t;
    while (t --> 0) {
        // операции позволяют переставлять все 2*n элементов как угодно
        // например, если мы хотим переставить a[i] и b[j], то делаем:
        // swap(a[i], a[j]) + swap(a[j], b[j]) + swap(a[i], a[j])
        // поэтому отсортируем все 2*n чисел и будем комбинировать в пары
        // в порядке убывания значений элементов
        int n; cin >> n;
        vector<int> c(2*n);
        for (int i = 0; i < 2 * n; i++)
            cin >> c[i];
        sort(c.begin(), c.end());
        int res = 0;
        for (int i = 0; i < 2 * n; i += 2)
            res += c[i] * c[i+1];
        cout << res << '\n';
    }
}
