#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
main() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // делим все числа на 2 пока делятся
    // ответ равен количеству различных чисел которые после этого остались
    for (auto &it : a)
        while (it % 2 == 0)
            it /= 2;
    sort(all(a));
    cout << unique(all(a)) - a.begin() << endl;
}
