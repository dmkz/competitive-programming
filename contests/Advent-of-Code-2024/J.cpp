#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
using ull = unsigned long long;
struct Bitset {
    vector<ull> data;
    Bitset(int n = 0) : data((n+63)/64) { }
    void set(int i, bool value = 1) {
        data[i/64] &= ~(ull(1) << (i % 64));
        data[i/64] |= (ull(value) << (i % 64));
    }
    Bitset &operator|=(const Bitset &other) {
        for (int g = 0; g < isz(data); g++)
            data[g] |= other.data[g];
        return *this;
    }
    int count() const {
        int answ{};
        for (int g = 0; g < isz(data); g++)
            answ += __builtin_popcountll(data[g]);
        return answ;
    }
};
void part1() {
    string s;
    vector<string> a;
    while (getline(cin, s))
        a.push_back(s);
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    int cnt9 = 0;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            cnt9 += (a[r][c] == '9');
    // i-й бит равен 1, если i-я девятка была собрана, иначе равен 0
    vector reachable(nRows, vector(nCols, Bitset(cnt9)));
    vector calculated(nRows, vector(nCols, false));
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] == '9') {
                reachable[r][c].set(--cnt9);
                calculated[r][c] = 1;
            }
    // O(n*m*COUNT_NINES/64)
    function<bool(int,int,char)> dfs =
    [&](int r, int c, char want) -> bool
    {
        if (r < 0 || r >= nRows) return false;
        if (c < 0 || c >= nCols) return false;
        if (a[r][c] != want) return false;
        if (calculated[r][c]) return true;
        if (want != '9')
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++)
                    if (dr * dr + dc * dc == 1)
                        if (dfs(r+dr, c+dc, want+1))
                            reachable[r][c] |= reachable[r+dr][c+dc];
        return (calculated[r][c] = true);
    };
    int64_t answ{};
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] == '0') {
                dfs(r,c,'0');
                answ += reachable[r][c].count();
            }
    cout << answ << endl;
}   
void part2() {
    string s;
    vector<string> a;
    while (getline(cin, s))
        a.push_back(s);
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    //int cnt9 = 0;
    //for (int r = 0; r < nRows; r++)
    //    for (int c = 0; c < nCols; c++)
    //        cnt9 += (a[r][c] == '9');
    vector count(nRows, vector(nCols, ull(0)));
    vector calculated(nRows, vector(nCols, false));
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] == '9') {
                count[r][c] = 1;
                calculated[r][c] = 1;
            }
    // O(n*m)
    function<ull(int,int,char)> dfs =
    [&](int r, int c, char want) -> ull
    {
        if (r < 0 || r >= nRows) return 0;
        if (c < 0 || c >= nCols) return 0;
        if (a[r][c] != want) return 0;
        if (calculated[r][c]) return count[r][c];
        if (want != '9')
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++)
                    if (dr * dr + dc * dc == 1)
                        count[r][c] += dfs(r+dr, c+dc, want+1);
        calculated[r][c] = true;
        return count[r][c];
    };
    int64_t answ{};
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] == '0')
                answ += dfs(r,c,'0');
    cout << answ << endl;
}
main() {
    part2();
}

