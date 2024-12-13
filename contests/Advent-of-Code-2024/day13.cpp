#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void part1() {
    // чтение
    string s;
    int64_t answer{};
    while (getline(cin, s)) {
        // Button A: X+49, Y+95
        int xa, ya;
        int code = sscanf(s.c_str(), "Button A: X+%d, Y+%d", &xa, &ya);
        assert(code == 2);
        getline(cin, s);
        int xb, yb;
        code = sscanf(s.c_str(), "Button B: X+%d, Y+%d", &xb, &yb);
        assert(code == 2);
        getline(cin, s);
        int xf, yf;
        code = sscanf(s.c_str(), "Prize: X=%d, Y=%d", &xf, &yf);
        assert(code == 2);
        int answ = INT_MAX;
        for (int cnta = 0; cnta <= 100; cnta++)
            for (int cntb = 0; cntb <= 100; cntb++)
                if (xa*cnta+xb*cntb==xf && ya*cnta+yb*cntb==yf) {
                    answ = min(answ, 3 * cnta + cntb);
                }
        if (answ < INT_MAX)
            answer += answ;
        if (!getline(cin, s))
            break;
    }
    cout << answer << endl;
}
using ll = long long;
ll det(ll a, ll b, ll c, ll d) {
    return a * d - b * c;
}
void part2() {
    // чтение
    string s;
    int64_t answer{};
    while (getline(cin, s)) {
        // Button A: X+49, Y+95
        ll xa, ya;
        int code = sscanf(s.c_str(), "Button A: X+%lld, Y+%lld", &xa, &ya);
        assert(code == 2);
        getline(cin, s);
        ll xb, yb;
        code = sscanf(s.c_str(), "Button B: X+%lld, Y+%lld", &xb, &yb);
        assert(code == 2);
        getline(cin, s);
        ll xf, yf;
        code = sscanf(s.c_str(), "Prize: X=%lld, Y=%lld", &xf, &yf);
        assert(code == 2);
        const ll add = 10000000000000LL;
        xf += add;
        yf += add;
        // решаем систему линейных уравнений:
        // xa*cnta+xb*cntb==xf
        // ya*cnta+yb*cntb==yf
        ll q = det(xa, xb, ya, yb);
        ll pa = det(xf, xb, yf, yb);
        ll pb = det(xa, xf, ya, yf);
        if (q != 0 && (pa % q == 0) && (pb % q == 0)) {
            ll cnta = pa / q;
            ll cntb = pb / q;
            if (cnta >= 0 && cntb >= 0) {
                answer += 3 * cnta + cntb;
            }
        }
        if (!getline(cin, s))
            break;
    }
    cout << answer << endl;
}
main() {
    part2();
}

