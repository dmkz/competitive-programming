#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
using pii = pair<int,int>;
using vpii = vector<pii>;
void part1() {
    int64_t answ{};
    string s;
    vector<string> a;
    while (getline(cin, s))
        a.push_back(s);
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    map<char, vpii> points;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] != '.')
                points[a[r][c]].emplace_back(r, c);
    vpii answer;
    for (const auto &[_, vec] : points)
        for (int i = 0; i < isz(vec); i++)
            for (int j = 0; j < isz(vec); j++)
                if (i != j) {
                    int dr = vec[j].first - vec[i].first;
                    int dc = vec[j].second - vec[i].second;
                    int r = vec[j].first + dr;
                    int c = vec[j].second + dc;
                    if (r >= 0 && r < nRows && c >= 0 && c < nCols)
                        answer.emplace_back(r, c);
                }
    sort(all(answer));
    answer.erase(unique(all(answer)), answer.end());
    cout << (answ = isz(answer)) << endl;
}
void part2() {
    int64_t answ{};
    string s;
    vector<string> a;
    while (getline(cin, s))
        a.push_back(s);
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    map<char, vpii> points;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] != '.')
                points[a[r][c]].emplace_back(r, c);
    vpii answer;
    for (const auto &[_, vec] : points)
        for (int i = 0; i < isz(vec); i++)
            for (int j = 0; j < isz(vec); j++)
                if (i != j) {
                    int dr = vec[j].first - vec[i].first;
                    int dc = vec[j].second - vec[i].second;
                    int r = vec[j].first;
                    int c = vec[j].second;
                    while (r >= 0 && r < nRows && c >= 0 && c < nCols) {
                        answer.emplace_back(r, c);
                        r += dr;
                        c += dc;
                    }
                }
    sort(all(answer));
    answer.erase(unique(all(answer)), answer.end());
    cout << (answ = isz(answer)) << endl;
}
main() {
    part2();
}

