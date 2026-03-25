#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
// функция merge обновляем значение текущего максимума и его количества
void merge(int &bestLen, int64_t &bestCnt, int currLen, int64_t currCnt) {
    if (bestLen < currLen) {
        bestLen = currLen;
        bestCnt = currCnt;
    } else if (bestLen == currLen)
        bestCnt += currCnt;
}
pair<int, int64_t> solve(const auto &y, int l, int r) {
    if (l + 1 >= r)
        return {0, 1};
    // делим пополам и считаем ответы для половин:
    int m = (l + r) / 2;
    auto [leftBestLen, leftBestCnt] = solve(y, l, m);
    auto [rightBestLen, rightBestCnt] = solve(y, m, r);
    // осталось учесть подстроки, которые пересекают середину
    // для левой половины подойдут суффиксы, левая точка которых находится ниже,
    // чем все остальные точки на суффиксе => ниже минимума
    int bestLen = 0; int64_t bestCnt = 1;
    vector<pair<int,int>> leftCand; // {высота суффикса, длина суффикса}
    int minLeftY = INT_MAX;
    for (int i = m-1; i >= l; i--) {
        if (y[i] < minLeftY) {
            leftCand.emplace_back(y[i], m-i);
            minLeftY = y[i];
        } else if (y[i] == minLeftY)
            leftCand.back().second = m-i;
    }
    // каждому префиксу из правой половины сопоставляем лучший суффикс из
    // левой половины. Суффиксы левой половины отсортированы, поэтому используем
    // два указателя.
    int minRightY = INT_MAX, j = 0;
    for (int i = m; i < r; i++) {
        minRightY = min(minRightY, y[i]);
        if (y[i] <= minRightY) {
            while (j < isz(leftCand) && leftCand[j].first > y[i])
                j++;
            int rightLen = i-m+1;
            if (j < isz(leftCand) && leftCand[j].first == y[i]) {
                int currLen = leftCand[j].second + rightLen - 1;
                merge(bestLen, bestCnt, currLen, 1);
            }
        }
    }
    merge(bestLen, bestCnt, leftBestLen, leftBestCnt);
    merge(bestLen, bestCnt, rightBestLen, rightBestCnt);
    return {bestLen, bestCnt};
}
main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s; cin >> s;
    // перейдём к геометрической интерпретации в виде точек (x, y):
    // x - длина префикса, y - баланс:
    vector<int> y(isz(s)+1);
    for (int i = 1; i < isz(y); i++)
        y[i] = y[i-1] + (s[i-1] == '(' ? +1 : -1);
    // и будем решать в ней:
    auto [maxLen, maxCnt] = solve(y, 0, isz(y));
    if (maxLen == 0)
        maxCnt = 1;
    cout << maxLen << ' ' << maxCnt << '\n';
}
