#include <bits/stdc++.h>
using namespace std;
const set<string> valid{"???????? ? ???????? ???????",
                        "??",
                        "???????????",
                        "???????",
                        "??????",
                        "??? ????",
                        "?????????????????",
                        "???????? ???????",
                        "????? ??????????"};
main() {
    string s;
    getline(cin, s);
    int t = stoi(s);
    while (t --> 0) {
        getline(cin, s);
        cout << valid.count(s) << "\n";
    }
}