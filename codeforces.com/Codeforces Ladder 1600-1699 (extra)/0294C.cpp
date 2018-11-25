/*
    Problem: 294C. Shaass and Lights
    
    Solution: math, combinatorics, O(n * log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <functional>

const int mod = (int)1e9+7;

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

int add(int a, int b) {
    return (a += b) >= mod ? a - mod : a;
}

int sub(int a, int b) {
    return (a -= b) < 0 ? a + mod : a;
}

int pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = mul(res, a);
        }
        n >>= 1;
        a = mul(a, a);
    }
    return res;
}

int inv(int a) {
    return pow(a, mod-2);
}

int main() {
    std::vector<int> fact(1+1000, 1), inv_fact(1+1000, 1);
    for (int i = 2; i <= 1000; ++i) {
        fact[i] = mul(fact[i-1], i);
        inv_fact[i] = inv(fact[i]);
    }
    std::function<int(int,int)> C = [&](int n, int k) {
        return mul(fact[n], mul(inv_fact[k], inv_fact[n-k]));
    };
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<int> in(n);
        for (int i = 0, v; i < m; ++i) {
            std::cin >> v;
            in[v-1] = 1;
        }
        int lt = 0, rt = n-1;
        while (lt < n && !in[lt]) ++lt;
        while (rt >= lt && !in[rt]) --rt;
        int rem = n - m, answ = 1;
        for (int p = lt; p < rt; ) {
            while (p < rt && in[p]) ++p;
            int sp = p;
            while (p < rt && !in[p]) ++p;
            int cnt = p - sp;
            answ = mul(answ, C(rem, cnt));
            answ = mul(answ, pow(2, cnt-1));
            rem -= cnt;
        }
        answ = mul(answ, C(rem, lt));
        std::cout << answ << std::endl;
    }
    return 0;
}