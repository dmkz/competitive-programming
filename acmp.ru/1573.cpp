#include <iostream>
#include <climits>
#include <cassert>

typedef long long ll;

inline ll pow(ll a, int n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res *= a;
        }
        a *= a;
        n >>= 1;
    }
    return res;
}

ll solve(ll num, int low) {
    if (low == 1) {
        return num+1;
    }
    if (num < (ll(1) << low)) {
        return ll(1) << low;
    }
    ll answ = LLONG_MAX;
    bool finished = false;
    for (int base = 2; !finished; ++base) {
        ll pow = ::pow(base, low);
        ll temp = (num+pow-1) / pow * pow;
        if (temp == num) {
            temp += pow;
        } else if (pow > num) {
            finished = true;
        }
        answ = std::min(answ, temp);
    }
    assert(answ > num && answ < LLONG_MAX);
    return answ;
}

int main() {
    ll num; int low; 
    std::cin >> num >> low;
    std::cout << solve(num, low);
    return 0;
}