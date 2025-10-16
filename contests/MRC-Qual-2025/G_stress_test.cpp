// Здесь находится поиск контр-тестов к решению путём полного перебора тестов и
// сравнения времени работы быстрого решения с медленным, но правильным

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// 3122122211-> 3|12|21|22|211
#define int int64_t
using namespace std;
template<typename Comp = std::less<int>>
struct Brute {
    
    string s;
    
    vector<int> stack;
    
    Brute(string s_) : s(s_) { }
    
    void dfs(const auto &f) {
        dfs(f, 0, (int)s.size(), 0);
    }
    
    void dfs(const auto &f, int i, int n, int prev = 0) {
        if (i == n) {
            f(stack);
            return;
        }
        for (int j = i; j < n; j++) {
            int num = stoll(s.substr(i, j-i+1));
            if (prev == 0 || Comp()(prev, num)) {
                stack.push_back(num);
                dfs(f, j+1,n,num);
                stack.pop_back();
            }
        }
    }
};

string slow(const string &s) {
    Brute bruteSuff(s);
    Brute<std::greater<int>> brutePref(s);
    int answ = stoll(s);
    bruteSuff.dfs(
        [&](const std::vector<int> &stack)
        {
            answ = min(answ, stack.back());
        }
    );
    brutePref.dfs(
        [&](const std::vector<int> &stack)
        {
            answ = min(answ, stack.front());
        }
    );
    return to_string(answ);
}
bool isGreater(const string &s, int a, int b, int c, int d) {
    if (b - a > d - c) return true;
    if (b - a < d - c) return false;
    return memcmp(s.c_str() + a, s.c_str() + c, d - c + 1) > 0;
}
string dp(const string &s) {    
    const int n = (int)s.size();
    vector dpR(n+1, vector<bool>(n+1));
    for (int i = 0; i < n; i++)
        dpR[i][n-1] = 1;
    dpR[n][n] = 1;
    auto answ = make_pair((int)s.size(), s);
    for (int i = n-1; i >= 0; i--)
        for (int j = i; j < n; j++)
            for (int k = j+1; k < n; k++)
                if (dpR[j+1][k] && isGreater(s, i, j, j+1, k)) {
                    dpR[i][j] = 1;
                }
    for (int j = 0; j < n; j++) {
        if (dpR[0][j]) {
            answ = min(answ, make_pair(j+1, s.substr(0, j+1)));
            break;
        }
    }
    vector dpL(n, vector<bool>(n));
    for (int i = 0; i < n; i++)
        dpL[i][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k < j; k++) {
                if (dpL[j-1][k] && isGreater(s, j, i, k, j-1)) {
                    dpL[i][j] = 1;
                }
            }
        }
    }
    for (int i = n-1; i >= 0; i--)
        if (dpL[n-1][i])
            answ = min(answ, make_pair(n-i, s.substr(i, n-i)));
    return answ.second;
}
string dpSmart(const string &s)
{
    const int n = (int)s.size();
    int maxAnswer = 1;
    while (maxAnswer * (maxAnswer+1) / 2 <= n)
        maxAnswer++;
    vector canLeft(n+1, vector<bool>(maxAnswer+1, false));
    vector canRight(n+1, vector<bool>(maxAnswer+1, false));
    vector canLeftSum(n+1, vector<int16_t>(maxAnswer+1, 0));
    vector canRightSum(n+1, vector<int16_t>(maxAnswer+1, 0));
    for (int len = 1; len <= n; len++) {
        for (int last = 1; last <= min(len, maxAnswer); last++) {
            // можно ли выбрать возрастающую последовательность на префиксе
            // длины len так, чтобы последнее число имело длину last
            // проверяем сначала меньшие предыдущие длины:
            bool ok = (canLeftSum[len - last][last - 1] > 0);
            if (ok) {
                canLeft[len][last] = true;
            } else {
                // иначе нужно проверять такую же длину
                int pos = len - 2 * last;
                if (pos >= 0 && canLeft[len - last][last] &&
                    isGreater(s, pos + last, len - 1, pos, pos + last - 1))
                {
                    canLeft[len][last] = true;
                }
            }
        }
        if (len <= maxAnswer && !canLeft[len][len])
            canLeft[len][len] = true;
        // предподсчитываем префикс-суммы для текущего столбца на будущее:
        canLeftSum[len][0] = canLeft[len][0];
        for (int i = 1; i <= maxAnswer; i++)
            canLeftSum[len][i] = canLeftSum[len][i-1] + canLeft[len][i];
    }
    // аналогично, но теперь справа-налево
    for (int len = 1; len <= n; len++) {
        for (int last = 1; last <= min(len, maxAnswer); last++) {
            // можно ли выбрать возрастающую последовательность на суффиксе
            // длины len так, чтобы последнее число имело длину last
            // проверяем сначала меньшие предыдущие длины:
            bool ok = (canRightSum[len - last][last - 1] > 0);
            if (ok) {
                canRight[len][last] = true;
            } else {
                // иначе нужно проверять такую же длину
                int pos = n - len;
                if (pos + 2 * last <= n && canRight[len - last][last] &&
                    isGreater(s, pos, pos + last - 1, pos + last, pos + 2 * last - 1))
                {
                    canRight[len][last] = true;
                }
            }
        }
        if (len <= maxAnswer && !canRight[len][len])
            canRight[len][len] = true;
        // предподсчитываем префикс-суммы для текущего столбца на будущее:
        canRightSum[len][0] = canRight[len][0];
        for (int i = 1; i <= maxAnswer; i++)
            canRightSum[len][i] = canRightSum[len][i-1] + canRight[len][i];
    }
    // выбираем лучший ответ:
    auto answer = make_pair(n, s);
    for (int prefLen = 1; prefLen <= maxAnswer; prefLen++)
        if (canRight[n][prefLen]) {
            answer = min(answer, make_pair(prefLen, s.substr(0, prefLen)));
            break;
        }
    for (int suffLen = 1; suffLen <= maxAnswer; suffLen++)
        if (canLeft[n][suffLen]) {
            answer = min(answer, make_pair(suffLen, s.substr(n - suffLen, suffLen)));
            break;
        }
    return answer.second;
}
void stress() {
    const int alphabet = 3;
    for (int len = 1; len <= 16; len++) {
        const int limit = pow(alphabet, len);
        string s(len, '1');
        for (int mask = 0; mask < limit; mask++) {
            for (int i = 0, temp = mask; i < len; i++) {
                s[i] = temp % alphabet + '1';
                temp /= alphabet;
            }
            auto ft = dpSmart(s);
            auto sl = dp(s);
            if (ft != sl) {
                cout << "Wrong answer" << endl;
                cout << s << endl;
                cout << "ft = " << ft << endl;
                cout << "sl = " << sl << endl;
                exit(0);
            }
        }
        cout << "len = " << len << ": OK" << endl;
    }
}
main() {
    //stress(); // раскоментировать если нужно протестировать
    string s;
    cin >> s;
    cout << dpSmart(s) << endl;
}
