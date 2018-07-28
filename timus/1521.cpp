/*
    Problem: 1521. War Games 2
    
    Solution: Fenwick, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <cassert>
#include <string>

int log2(int n) {
    int pow = 0;
    while ((1 << (pow+1)) <= n) {
        ++pow;
    }
    return pow;
}

struct Fenwick {
    
    const int size, pow2;
    
    std::vector<int> data;
    
    Fenwick(const std::vector<bool>& a) 
        : size((int)a.size())
        , pow2(1 << log2(size))
    {
        data.resize(size);
        for (int i = 0; i < (int)a.size(); i++) {
            inc(i, a[i]);
        }
    }

    // Sum on segment [0, r]:
    int sum(int r) const {
        int result = 0;
        for (; r >= 0; r = (r & (r+1)) - 1) {
            result += data[r];
        }
        return result;
    }

    // Increase value on position `p` by delta:
    void inc(int p, int delta) {
        for (; p < size; p = (p | (p+1))) {
            data[p] += delta;
        }
    }

    // Sum on segment [l, r]:
    int sum (int l, int r) const {
        return sum(r) - sum(l-1);
    }
    
    // Lower bound for sum `s`: sum[0]+...+sum[p-1] < s >= sum[0]+...+sum[p]
    int lower_bound(int s) const {
        int pos = 0;
        for (int p = pow2; p >= 1; p /= 2) {
            if (pos + p - 1 < size && data[pos + p - 1] < s) {
                s -= data[pos + p - 1];
                pos += p;
            }
        }
        return pos;
    }  
};

int main() {
    int n, step;
    scanf("%d %d", &n, &step);
    
    Fenwick fw(std::vector<bool>(1+n,1));
    fw.inc(0,-1);
    for (int i = 0, p = 1; i < n; ++i) {
        int s = step;
        if (fw.sum(p, n) < s) {
            s -= fw.sum(p, n);
            p = 1;
            int t = fw.sum(p, n);
            s %= t;
            if (s == 0) s = t;
        }
        p = fw.lower_bound(s+fw.sum(p-1));
        printf("%d ", p);
        fw.inc(p, -1);
    }
    return 0;
}