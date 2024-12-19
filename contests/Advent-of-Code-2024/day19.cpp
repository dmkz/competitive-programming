#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void part1() {
    string s;
    getline(cin, s);
    vector<string> towels;
    istringstream input(s);
    while (input >> s) {
        if (s.size() && s.back() == ',')
            s.pop_back();
        if (s.size())
            towels.emplace_back(s);
    }
    getline(cin, s); // пустая строчка
    // читаем наборы:
    int64_t answ{};
    while (getline(cin, s)) {
        vector<char> possible(isz(s)+1, false);
        possible[0] = true;
        for (int prefLen = 1; prefLen <= isz(s); prefLen++)
            for (const auto &t : towels)
                if (prefLen >= isz(t)) {
                    bool match = true;
                    for (int i = 1; i <= isz(t); i++)
                        match &= (t[isz(t)-i] == s[prefLen-i]);
                    if (match)
                        possible[prefLen] |= possible[prefLen - isz(t)];
                }
        answ += possible[isz(s)];
    }
    cout << answ << endl;
}
void part2() {
    string s;
    getline(cin, s);
    vector<string> towels;
    istringstream input(s);
    while (input >> s) {
        if (s.size() && s.back() == ',')
            s.pop_back();
        if (s.size())
            towels.emplace_back(s);
    }
    getline(cin, s); // пустая строчка
    // читаем наборы:
    int64_t answ{};
    while (getline(cin, s)) {
        vector<int64_t> numWays(isz(s)+1, 0);
        numWays[0] = 1;
        for (int prefLen = 1; prefLen <= isz(s); prefLen++)
            for (const auto &t : towels)
                if (prefLen >= isz(t)) {
                    bool match = true;
                    for (int i = 1; i <= isz(t); i++)
                        match &= (t[isz(t)-i] == s[prefLen-i]);
                    if (match)
                        numWays[prefLen] += numWays[prefLen - isz(t)];
                }
        answ += numWays[isz(s)];
    }
    cout << answ << endl;
}
main() {
    part2();
}


