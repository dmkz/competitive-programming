#include <bits/stdc++.h>
using namespace std;

int64_t C(int n, int k) {
    int64_t res = 1;
    for (int i = 1; i <= k; i++) {
        res *= (n-i+1);
        res /= i;
    }
    return res;
}

const int INF = (int)1e9+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    map<int,int> cnt;
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        cnt[a]++;
    }
    // ответ включает в себя <= 3 минимума
    // можно просто перебрать сколько какого минимума мы возьмём в ответ и выбрать минимальный способ
    // вместо того чтобы расписывать if-ы
    vector<int> min, cntMin;
    for (auto [item, count] : cnt) {
        cntMin.push_back(count);
        min.push_back(0);
    }
    while (cntMin.size() < 3u) {
        cntMin.push_back(0);
        min.push_back(INF);
    }
    __int128 minRes = 1e36L+100;
    int64_t nWays = 0;
    for (int n0 = 0; n0 <= 3; n0++) { // сколько берём первого минимума
        for (int n1 = 0; n0 + n1 <= 3; n1++) { // сколько берём второго минимума
            int n2 = 3 - n0 - n1; // сколько берём третьего минимума
            if (n0 > cntMin[0] || n1 > cntMin[1] || n2 > cntMin[2])
                continue;
            auto res = __int128(powl(min[0], n0)) * powl(min[1], n1) * powl(min[2], n2);
            if (res < minRes) {
                res = minRes;
                nWays = C(cntMin[0], n0) * C(cntMin[1], n1) * C(cntMin[2], n2);
            }
        }
    }
    cout << nWays << endl;
}
