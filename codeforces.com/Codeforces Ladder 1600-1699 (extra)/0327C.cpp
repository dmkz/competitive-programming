/*
    Problem: 327C. Magic Five
    
    Solution: geometric progression, number theory, combinatorics, math, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmozyrev@rambler.ru
*/

#include <iostream>
#include <string>

const int mod = (int)1e9+7;

int add(int a, int b) {
    return (a += b) >= mod ? a - mod : a;
}

int sub(int a, int b) {
    return (a -= b) < 0 ? a + mod : a;
}

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

int pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}

int geom(int a, int n) {
    // 1 + a + a^2 + a^3 + ... + a^(n-1)
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else if (n % 2 == 1) {
        return add(1, mul(a, geom(a, n-1)));
    } else {
        return mul(add(1, a), geom(mul(a, a), n / 2));
    }
}

int main() {
    std::string s; int k;
    while (std::cin >> s >> k) {
        int res = 0, n = (int)s.size();
        for (int pos = n-1; pos >= 0; --pos) {
            if (s[pos] == '0' || s[pos] == '5') {
                res = add(res, pow(2, pos));
            }
        }
        res = mul(res, geom(pow(2, n), k));
        std::cout << res << std::endl;
    }
    return 0;
}