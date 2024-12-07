#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define int int64_t
using namespace std;
void part1() {
    int64_t answ{};
    string s;
    while (getline(cin, s)) {
        stringstream ss(s);
        int64_t result;
        ss >> result;
        char ch;
        ss >> ch;
        assert(ch == ':');
        vector<int> a;
        for (int x; ss >> x; a.push_back(x));
        bool ok = false;
        for (int mask = 0; mask < (1 << (isz(a)-1)); mask++) {
            long double temp = a[0];
            for (int bit = 0; bit < isz(a)-1; bit++)
                if ((mask >> bit) & 1) temp *= a[bit+1];
                else temp += a[bit+1];
            if (temp == (long double)result) {
                ok = true;
                break;
            }
        }
        if (ok) answ += result;
    }
    cout << answ << endl;
}
void concat(auto &dst, int src) {
    int pow10 = 1;
    while (pow10 <= src)
        pow10 *= 10;
    dst = dst * pow10 + src;
}
void part2() {
    int64_t answ{};
    string s;
    while (getline(cin, s)) {
        stringstream ss(s);
        int64_t result;
        ss >> result;
        char ch;
        ss >> ch;
        assert(ch == ':');
        vector<int> a;
        for (int x; ss >> x; a.push_back(x));
        const int limit = (int)pow(3, isz(a)-1);
        bool ok = false;
        for (int mask = 0; mask < limit; mask++) {
            long double currResult = a[0];
            for (int bit = 0, temp = mask; bit < isz(a)-1; bit++)
            {
                int currOp = temp % 3;
                temp /= 3;
                switch (currOp) {
                    case 0: currResult *= a[bit+1]; break;
                    case 1: currResult += a[bit+1]; break;
                    case 2: concat(currResult, a[bit+1]); break;
                    default: assert(false);
                };
            }
            if (currResult == (long double)result) {
                ok = true;
                break;
            }
        }
        if (ok)
            answ += result;
    }
    cout << answ << endl;
}
main() {
    part2();
}
