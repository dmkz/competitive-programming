#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
const int mod = (int)1e9+7;
int& add(int& a, int b) {
    return (a += b) >= mod ? (a -= mod) : a;
}
int solve(const int curr, const int need, const string& s) {
// считаем баланс и минимальный префикс подстроки:
    int givenBalance = 0, minPref = 0;
    for (auto it : s) {
        givenBalance += (it == '(' ? +1 : -1);
        minPref = std::min(minPref, givenBalance);
    }
    if (abs(givenBalance) > need-curr)
        return 0; // ничего не получится
// иначе считаем ответ динамическим программированием:
    int mxLen = need - curr + 1;
    vvvi count(2, vvi(1+mxLen, vi(1+mxLen)));
    // count[used s][len][balance]
    count[0][0][0] = 1;
    for (int used = 0; used < 2; ++used)
        for (int len = 0; len < mxLen; ++len)
            for (int balance = 0; balance <= mxLen; ++balance) {
                const int currCnt = count[used][len][balance];
                // ставим закрывающую скобку:
                if (balance > 0)
                    add(count[used][len+1][balance-1], currCnt);
                // ставим открывающую скобку:
                if (balance+1 <= mxLen)
                    add(count[used][len+1][balance+1], currCnt);
                // ставим строку "s" целиком:
                if (used == 0 &&
                    balance + minPref >= 0 &&
                    balance + givenBalance <= mxLen
                )
                    add(count[used+1][len+1][balance+givenBalance], currCnt);
            }
    return count[1][mxLen][0];
}
main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int curr, need;
    string s;
    while (cin >> need >> curr >> s)
        cout << solve(curr, need, s) << endl;
}
