// сортировка, два указателя
#include <bits/stdc++.h>
using namespace std;
const int inf = (int)2e9+7;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем и сортируем координаты деревень и вышек:
    int n, m;
    cin >> n >> m;
    vector<int> villages(n), towers(m);
    for (int i = 0; i < n; i++)
        cin >> villages[i];
    for (int i = 0; i < m; i++)
        cin >> towers[i];
    sort(villages.begin(), villages.end());
    sort(towers.begin(), towers.end());
    // решаем задачу:
    int j = 0, answ = 0;
    for (int i = 0; i < n; i++) {
        // находим расстояние от i-й деревни до ближайшей вышки
        // для этого мы должны найти ближайшую справа и ближайшую слева
        // используем два указателя
        while (j < m && towers[j] <= villages[i])
            j++;
        int currDist = inf;
        if (j < m)
            currDist = min(currDist, towers[j] - villages[i]);
        if (j-1 >= 0)
            currDist = min(currDist, villages[i] - towers[j-1]);
        // обновлям ответ:
        answ = max(answ, currDist);
    }
    cout << answ << endl;
}
