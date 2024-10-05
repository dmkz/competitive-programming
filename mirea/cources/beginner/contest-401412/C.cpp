#include <bits/stdc++.h>
using namespace std;
const int INF = (int)3e8+10;
int main() {
    // читаем данные:
    int n; cin >> n;
    vector<int> s(n), c(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];
    for (int i = 0; i < n; i++)
        cin >> c[i];
    // предподсчитываем значение: minCostSuff[i] - стоимость c[j] минимального
    // баннера s[j] на отрезке [i+1, n-1] при условии, что s[i] < s[j]:
    vector<int> minCostSuff(n, INF);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (s[i] < s[j])
                minCostSuff[i] = min(minCostSuff[i], c[j]);
    // теперь из тройки ijk такой что s[i] < s[j] < s[k] переберём только i и j,
    // так как оптимальное k можем находить за O(1)
    int bestAnsw = INF;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (s[i] < s[j])
                bestAnsw = min(bestAnsw, c[i] + c[j] + minCostSuff[j]);
    // если получилась бесконечность или больше, то надо выводить -1:
    if (bestAnsw >= INF)
        bestAnsw = -1;
    // выводим ответ:
    cout << bestAnsw << endl;
}