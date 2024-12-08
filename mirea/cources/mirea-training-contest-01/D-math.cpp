#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    // читаем данные:
    int nRows, nCols;
    cin >> nRows >> nCols;
    int nTrees; cin >> nTrees;
    vector<pair<int,int>> trees(nTrees);
    for (auto &[x, y] : trees)
        cin >> x >> y;
    // находим ответ:
    tuple<int,int,int> maxDistXY = {INT_MIN, 0, 0};
    for (int r = 1; r <= nRows; r++)
        for (int c = 1; c <= nCols; c++) {
            // переберём все деревья, считая расстояние до каждого:
            int minDistToTree = INT_MAX;
            for (int i = 0; i < nTrees; i++) {
                int dx = r - trees[i].first;
                int dy = c - trees[i].second;
                int currDist = abs(dx) + abs(dy);
                minDistToTree = min(minDistToTree, currDist);
            }
            // обновить ответ:
            maxDistXY = max(maxDistXY, make_tuple(minDistToTree, r, c));
        }
    // выводим ответ:
    auto [_, x, y] = maxDistXY; // x = get<1>(minDistXY), y = get<2>(minDistXY)
    cout << x << ' ' << y << endl;
}
