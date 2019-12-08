/*
    Problem: 300C. Beautiful Numbers
    Solution: brute force, combinatorics
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

const int mod = (int)1e9+7;

typedef long long ll;

int pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = int(ll(res) * a % mod);
        }
        a = int(ll(a) * a % mod);
        n /= 2;
    }
    return res;
}

inline int inverse(int a) {
    return pow(a, mod-2);
}

int main() {    
    int a, b, n, answ = 0; 
    std::cin >> a >> b >> n;
    std::vector<int> fact(1+n, 1);
    
    for (int i = 2; i <= n; ++i) {
        fact[i] = int((ll)fact[i-1] * i % mod);
    }
    
    std::function<int(int,int)> C = [&](const int n_, const int k) {
        return int((ll)fact[n_] * inverse(fact[k]) % mod * inverse(fact[n_-k]) % mod);
    };
    
    // k * a + (n - k) * b - good?
    for (int k = 0; k <= n; ++k) {
        int sum = k * a + (n - k) * b;
        bool flag = true;
        do {
            int digit = sum % 10;
            sum /= 10;
            if (!(digit == a || digit == b)) {
                flag = false;
                break;
            }
        } while (sum > 0);
        if (flag) {
            answ = (answ + C(n, k)) % mod;
        }
    }
    std::cout << answ;
    return 0;
}