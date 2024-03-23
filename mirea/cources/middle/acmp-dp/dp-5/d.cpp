#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем число кубиков
    int n; cin >> n;
    // считаем динамику
    map<pair<int,int>, int> dp; // dp[n][k] = число лесенок из n кубиков, верхняя строка которой <= k
    function<int(int,int)> solve = [&](int n, int k) {
        // если значение уже посчитано, то возвращаем его:
        if (auto it = dp.find({n,k}); it != dp.end())
            return it->second;
        // иначе считаем честно
        if (n == 0) // крайний случай, когда не осталось кубиков
            return 1;
        // иначе есть кубики и перебираем каждый из min(n, k) переходов
        int &res = dp[{n,k}];
        for (int currRow = 1; currRow <= min(n, k); currRow++) {
            // укладываем строку из currRow кубиков и считаем сколько вариантов
            // уложить сверху оставшиеся n-CurrRow кубиков при условии, что
            // следующая строка должна быть < currRow, то есть <= (currRow-1)
            res += solve(n-currRow, currRow-1);
        }
        return res;
    };
    
    // выводим ответ:
    cout << solve(n,n) << endl;
}
