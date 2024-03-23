#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем переходы
    map<char, string> next;
    for (char c : {'N', 'S', 'W', 'E', 'U', 'D'})
        getline(cin, next[c]);
    // читаем начальное состояние
    char s; int n;
    cin >> s >> n;
    // считаем ленивую динамику
    map<pair<char,int>, int> dp;
    function<int(char,int)> solve = [&](char curr, int steps) {
        // если динамика уже посчитана, то возвращаем ответ на неё:
        if (auto it = dp.find({curr,steps}); it != dp.end())
            return it->second;
        // иначе считаем нормально:
        int &res = dp[{curr,steps}];
        res = 1;
        if (steps > 1)
            for (char c : next[curr])
                res += solve(c, steps-1);
        return res;
    };
    cout << solve(s,n) << endl;
}
