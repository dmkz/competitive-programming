/*
    Problem: 154B. Colliders
    
    Solution: primes, divisors, number theory, O(n + m * sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef std::vector<int> vi;

vi factor(int v) {
    vi ans;
    for (int i = 2; i * i <= v; ++i) {
        if (v % i == 0) {
            ans.push_back(i);
            while (v % i == 0) v /= i;
        }
    }
    if (v > 1) {
        ans.push_back(v);
    }
    return ans;
}

int main() {
    int n, q;
    while (std::cin >> n >> q) {
        vi state(1+n, false), which(1+n, 0);
        for (int i = 0; i < q; ++i) {
            std::string s; int v;
            std::cin >> s >> v;
            vi primes = factor(v);
            if (s[0] == '+') {
                if (state[v]) {
                    std::cout << "Already on\n";
                    continue;
                }
                int j = 0;
                for (int p : primes) {
                    j = std::max(j, which[p]);
                }
                if (j != 0) {
                    std::cout << "Conflict with " << j << "\n";
                    continue;
                }
                state[v] = true;
                for (int p : primes) {
                    which[p] = v;
                }
                std::cout << "Success\n";
            } else {
                assert(s[0] == '-');
                if (!state[v]) {
                    std::cout << "Already off\n";
                } else {
                    state[v] = false;
                    for (int p : primes) {
                        which[p] = 0;
                    }
                    std::cout << "Success\n";
                }
            }
        }
    }    
    return 0;
}