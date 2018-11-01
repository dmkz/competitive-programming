/*
    Problem: 288B. Polo the Penguin and Houses
    
    Solution: graphs, cycles, brute force, math, combinatorics, O(n + k^(k+1))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

typedef long long ll;

const ll mod = (ll)1e9+7;

ll solve(int n, int k) {
    ll mul = 1;
    for (int i = k; i < n; ++i) {
        (mul *= (n - k)) %= mod;
    }
    int limit = 1;
    for (int i = 0; i < k; ++i) {
        limit *= k;
    }
    std::vector<int> next(k), prev(k), color(k), can(k);
    static int stack[16], size = 0;
    int answ = 0;
    for (int mask = 0; mask < limit; ++mask) {
        size = 0;
        for (int i = 0, temp = mask; i < k; ++i) {
            int div = temp / k;
            int rem = temp - div * k;
            next[i] = rem;
            prev[rem] = i;
            temp = div;
        }
        for (int i = 0; i < k; ++i) {
            color[i] = 0;
            can[i] = false;
        }
        bool flag = true;
        for (int i = 0; i < k; ++i) {
            if (color[i] == 0) {
                stack[size++] = i;
                color[i] = 1;
                while (size > 0) {
                    int u = stack[size-1];
                    int v = next[u];
                    if (v == 0) {
                        can[u] = true;
                        --size;
                        color[u] = 2;
                    } else if (color[v] == 1) {
                        can[u] = false;
                        can[v] = false;
                        color[u] = 2;
                        color[v] = 2;
                        --size;
                    } else if (color[v] == 2) {
                        can[u] = can[v];
                        color[u] = 2;
                        --size;
                    } else {
                        color[v] = 1;
                        stack[size++] = v;
                    }
                }
            }
            if (!can[i]) {
                flag = false;
                break;
            }
        }
        answ += flag;
    }
    return answ * mul % mod;
}

int main() {
    int n, k;
    while (std::cin >> n >> k) {
        std::cout << solve(n, k) << std::endl;
    }
    return 0;
}