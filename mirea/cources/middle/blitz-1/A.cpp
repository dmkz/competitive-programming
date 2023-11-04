#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // максимальное число простых это когда мы используем только двойки и тройки
    // а точнее, все двойки, и, возможно, одну тройку, если число нечётное
    int n; cin >> n;
    vector<int> a;
    while (n >= 2) { // набираем двойки пока можем
        a.push_back(2);
        n -= 2;
    }
    if (n == 1) // заменяем последнюю двойку на тройку
        a.back() = 3;
    // выводим ответ:
    cout << a.size() << endl;
    for (auto it : a)
        cout << it << ' ';
    cout << endl;
}
