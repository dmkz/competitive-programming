#include <bits/stdc++.h>
using namespace std;
const int maxC = 100000;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем веса предметов и проверяемый вес:
    int n, c; cin >> n >> c;
    vector<int> w(n);
    for (auto& it : w)
        cin >> it;
    // Бит с номером x показывает, достижим ли вес x.
    bitset<maxC + 1> possible;
    // Пустое подмножество имеет вес 0.
    possible[0] = 1;
    // Сдвиг создаёт варианты с предметом i, а | сохраняет варианты без него.
    for (int i = 0; i < n; i++)
        possible |= possible << w[i];
    if (possible[c]) cout << "YES\n";
    else cout << "NO\n";
}