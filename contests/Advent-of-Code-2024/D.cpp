#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void thisFunctionDoesNotSolveOriginalProblem() {
    string s;
    vector<string> a;
    while (getline(cin, s))
        a.push_back(s);
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    const string t = "XMAS";
    vector count(isz(t), vector(nRows, vector<int>(nCols, 0)));
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            count[0][r][c] = (a[r][c] == 'X');
    for (int i = 1; i < isz(t); i++)
        for (int r = 0; r < nRows; r++)
            for (int c = 0; c < nCols; c++)
                if (a[r][c] == t[i])
                    for (int dr = -1; dr <= 1; dr++)
                        for (int dc = -1; dc <= 1; dc++)
                            if (dr * dr + dc * dc == 1) {
                                int nr = r + dr;
                                int nc = c + dc;
                                if (nr < 0 || nr >= nRows) continue;
                                if (nc < 0 || nc >= nCols) continue;
                                count[i][r][c] += count[i-1][nr][nc];
                            }
    int answ = 0;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            answ += count[isz(t)-1][r][c];
    cout << answ << endl;
}
void part1() {
    string s;
    vector<string> a;
    while (getline(cin, s))
        a.push_back(s);
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    const string t = "XMAS";
    int answ = 0;
    for (int sr = 0; sr < nRows; sr++)
        for (int sc = 0; sc < nCols; sc++)
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++)
                    if (dr * dr + dc * dc > 0) {
                        int r = sr, c = sc, i = 0;
                        for (; i < isz(t); ) {
                            if (0 <= r && r < nRows &&
                                0 <= c && c < nCols &&
                                a[r][c] == t[i])
                            {
                                r += dr;
                                c += dc;
                                i++;
                            } else {
                                break;
                            }
                        }
                        answ += (i == isz(t));
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
    int answ = 0;
    for (int sr = 1; sr + 1 < nRows; sr++)
        for (int sc = 1; sc + 1 < nCols; sc++)
            if (a[sr][sc] == 'A') {
                int cnt1[256]{}, cnt2[256]{};
                cnt1[a[sr-1][sc-1]]++;
                cnt1[a[sr+1][sc+1]]++;
                cnt2[a[sr-1][sc+1]]++;
                cnt2[a[sr+1][sc-1]]++;
                answ += (cnt1['M'] && cnt1['S'] && cnt2['M'] && cnt2['S']);
            }
            
    cout << answ << endl;
}
main() {
    part2();
}
