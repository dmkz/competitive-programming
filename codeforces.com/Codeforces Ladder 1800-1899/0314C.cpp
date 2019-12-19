/*
    Problem: 314C. Sereja and Subsequences
    Solution: math, combinatorics, dynamic programming, Fenwick, O(n log(n))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
template<int mod>
struct Number {
    int data;
    Number(int data_ = 0) : data(data_) { }
    Number& operator+=(Number other) { return (data += other.data) >= mod ? data -= mod, *this : *this; }
    Number& operator-=(Number other) { return (data -= other.data) < 0 ? data += mod, *this : *this; }
    Number operator+(Number other) const { return other += *this; }
    Number operator-(Number other) const { return Number(*this) -= other; }
    Number operator*(Number other) const { return Number(int(data * 1LL * other.data % mod)); }
    Number& operator*=(Number other) { return *this = *this * other; }
};
template<typename T>
struct Fenwick {
    std::vector<T> data;
    Fenwick(int n) : data(n, T(0)) { }
    T operator()(int r) const {
        T res(0);
        while (r >= 0) {
            res += data[r];
            r = (r & (r + 1)) - 1;
        }
        return res;
    }
    T operator()(int l, int r) const {
        return (*this)(r) - (l > 0 ? (*this)(l-1) : T(0));
    }
    void inc(int p, T x) {
        for (int i = p; i < isz(data); i |= i+1) data[i] += x;
    }
};
const int mod = (int)1e9+7, AMAX = (int)1e6;
using Int = Number<mod>;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        Fenwick<Int> fw(1+AMAX);
        std::vector<int> arr(n);
        for (auto &it : arr) std::cin >> it;
        Int answ(0);
        for (int i = 0, a; i < n; i++) {
            a = arr[i];
            auto curr = (fw(a) + 1) * a - fw(a,a);
            fw.inc(a,curr);
            answ += curr;
        }
        std::cout << answ.data << std::endl;
    }
    return 0;
}