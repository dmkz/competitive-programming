#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void part1() {
    std::string s;
    for (std::string ss; std::getline(cin, ss); s += ss);
    int p = 0, answ = 0;
    while (p < isz(s)) {
        p = (int)s.find("mul(", p);
        if (p == -1)
            break;
        p += 4;
        // "число,число)"
        // std::format
        int x, y;
        int code = sscanf(s.c_str()+p, "%d,%d", &x, &y);
        if (code == 2) {
            // прочитала два числа через запятую
            int mn = min(x, y);
            int mx = max(x, y);
            if (1 <= mn && mx <= 999) {
                string t = std::format("{},{})",x,y);
                if (t == s.substr(p, isz(t))) {
                    answ += x * y;
                }
            }
        }
    }
    cout << answ << endl;
}
void part2() {
    std::string s;
    for (std::string ss; std::getline(cin, ss); s += ss);
    uint64_t p = 0, answ = 0, enabled = true;
    while (p < s.size()) {
        uint64_t pMul = s.find("mul(", p);
        uint64_t pDo = s.find("do()", p);
        uint64_t pDont = s.find("don't()", p);
        uint64_t pMin = min({pMul,pDo,pDont});
        if (pMin >= s.size())
            break;
        if (pMin == pMul) {
            p = pMul + 4;
            // "число,число)"
            // std::format
            int x, y;
            int code = sscanf(s.c_str()+p, "%d,%d", &x, &y);
            if (code == 2) {
                // прочитала два числа через запятую
                int mn = min(x, y);
                int mx = max(x, y);
                if (1 <= mn && mx <= 999) {
                    string t = std::format("{},{})",x,y);
                    if (t == s.substr(p, isz(t)))
                        if (enabled) {
                            cout << "add " << x << " * " << y << endl;
                            answ += x * y;
                        }
                }
            }
        } else if (pMin == pDo) {
            p = pDo + 4; // do()
            enabled = true;
            cout << "enabled = true, pDo = " << pDo << endl;
        } else {
            assert(pMin == pDont);
            enabled = false;
            p = pDont + 7; // don't()
            cout << "enabled = false, pDont = " << pDont << endl;
        }
    }
    cout << answ << endl;
}
main() {
    part2();
}
