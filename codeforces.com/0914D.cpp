/*
    Problem: 0914D. Bash and a Tough Math Puzzle
    
    Solution: Sqrt-Decomposition, O(n sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/


#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

struct SqrtDecomposition {
    
    std::vector<int> arr;
    
    std::vector<int> gcd;
    
    const int GSIZE = 512;
    
    SqrtDecomposition(int size, int value = 1) {
        arr.assign(size, value);
        gcd.assign((size + GSIZE - 1) / GSIZE, value);
    }
    
    SqrtDecomposition(const std::vector<int>& arr_) : arr(arr_) {
        gcd.resize(((int)arr.size() + GSIZE - 1) / GSIZE);
        for (int g = 0; g < (int)gcd.size(); ++g) {
            update(g);
        }
    }
    
    void update(int g) {
        int l = g * GSIZE;
        int r = std::min(l + GSIZE, (int)arr.size())-1;
        int d = arr[l];
        for (int i = l + 1; i <= r; ++i) {
            d = ::gcd(d, arr[i]);
        }
        gcd[g] = d;
    }
    
    void set(int pos, int value) {
        arr[pos] = value;
        update(pos / GSIZE);
    }
    
    bool get(int l, int r, int value) const {
        int gl = l / GSIZE;
        int gr = r / GSIZE;
        int count = 0;
        if (gl == gr) {
            for (int i = l; count < 2 && i <= r; ++i) {
                count += (arr[i] % value != 0);
            }
        } else {
            for (int i = l; count < 2 && i < (gl+1) * GSIZE; ++i) {
                count += (arr[i] % value != 0);
            }
            for (int i = gr * GSIZE; count < 2 && i <= r; ++i) {
                count += (arr[i] % value != 0);
            }
            for (int g = gl + 1; count < 2 && g < gr; ++g) {
                if (gcd[g] % value != 0) {
                    for (int i = g * GSIZE; count < 2 && i < (g+1) * GSIZE; ++i) {
                        count += (arr[i] % value != 0);
                    }
                }
            }
        }
        return count < 2;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<int> arr(n);
    
    for (auto& it : arr) std::cin >> it;
    
    SqrtDecomposition sd(arr);
    
    int q; std::cin >> q;
    while (q--) {
        int t; std::cin >> t;
        if (t == 1) {
            int l, r, x; 
            std::cin >> l >> r >> x;
            --l, --r;
            std::cout << (sd.get(l, r, x) ? "YES\n" : "NO\n");
        } else {
            int p, x; std::cin >> p >> x;
            --p;
            sd.set(p, x);
        }
    }
    return 0;
}