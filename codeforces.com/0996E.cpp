/*
    Problem: 996E. Leaving the Bar
    
    Solution: brute force, greedy, geometry, random, O(32*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <memory>
#include <chrono>
#include <random>

typedef long double Real;

const Real eps = 1e-12L;

struct Vector {
    Real x, y;
    Vector(Real x_ = 0, Real y_ = 0) : x(x_), y(y_) { }
    Vector& operator-=(const Vector& other) { x -= other.x, y -= other.y; return *this; }
    Vector& operator+=(const Vector& other) { x += other.x, y += other.y; return *this; }
    Vector& operator*=(const Real & value) { x *= value, y *= value; return *this; }
};

Vector operator-(const Vector &a, const Vector &b) { return Vector(a) -= b; }
Vector operator+(const Vector &a, const Vector &b) { return Vector(a) += b; }
Vector operator*(const Vector &a, const Real value) { return Vector(a) *= value; }
Real dot(const Vector &a, const Vector &b) { return a.x * b.x + a.y * b.y; }
Real norm(const Vector &a) { return std::sqrt(dot(a,a)); }

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<Vector> arr(n);
        for (auto &it : arr) { std::cin >> it.x >> it.y; }
        std::vector<int> inverseFrom(n+1);
        std::vector<int> id(n);
        for (int i = 0; i < n; ++i) { id[i] = i; }
        uint64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        seed ^= uint64_t(std::make_unique<char>().get());
        std::mt19937 gen(seed);
        std::uniform_int_distribution<int> dist(0, n-1);
        for (int i = 0; i < n / 2; ++i) {
            int lt = dist(gen);
            int rt = dist(gen);
            std::swap(arr[lt], arr[rt]);
            std::swap(id[lt], id[rt]);
        }
        
        while (n > 1) {
            int nBrute = std::min(5, n);
            Real limit = ((nBrute == n) ? 1.5e6 : 1e18L) + eps;
            int bestMask = -1; Vector bestVector(1e9, 1e9);
            for (int mask = 0; mask < (1 << nBrute); ++mask) {
                Vector p;
                for (int bit = 0; bit < nBrute; ++bit) {
                    if ((mask >> bit) & 1) {
                        p += arr[n - nBrute + bit];
                    } else {
                        p -= arr[n - nBrute + bit];
                    }
                }
                if (norm(p) <= limit && norm(p) <= norm(bestVector)) {
                    bestVector = p;
                    bestMask = mask;
                }
            }
            assert(bestMask != -1);
            int mask = bestMask;
            for (int bit = 0; bit < nBrute; ++bit) {
                if ((mask >> bit) & 1) {
                    // nothing 
                } else {
                    inverseFrom[n - nBrute + bit]++;
                    if (bit+1 < nBrute) {
                        inverseFrom[n - nBrute + bit + 1]--;
                    }
                }
            }
            n = n - nBrute + 1;
            for (int i = 0; i < nBrute; ++i) { arr.pop_back(); }
            arr.push_back(bestVector);
        }
        std::vector<int> answ(id.size());
        for (int i = 0, balance = 0; i+1 < (int)inverseFrom.size(); ++i) {
            (balance += inverseFrom[i]) %= 2;
            answ[id[i]] = (balance ? +1 : -1);
        }
        for (auto it : answ) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}