#include <bits/stdc++.h>
using namespace std;
main() {
    // стреляем по нечётным клеткам до n не включительно
    // затем добиваем, стреляя в самую последнюю клетку
    int n; cin >> n;
    vector<int> a;
    for (int low = 1; low < n; low += 2)
        a.push_back(low);
    a.push_back(n);
    cout << a.size() << '\n';
    for (auto it : a)
        cout << it << ' ';
}
