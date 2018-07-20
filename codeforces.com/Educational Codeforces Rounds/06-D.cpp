/*
    Problem: 620D. Professor GukiZ and Two Arrays
    
    Solution: sorting, binary search, O(n^2 log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <numeric>

typedef int64_t Int;

template<typename T>
Int sum(const std::vector<T>& a) {
    return std::accumulate(a.begin(), a.end(), T(0));
}

std::vector<Int> step1(const std::vector<Int>& a, const std::vector<Int>& b) {
    Int suma = sum(a);
    Int sumb = sum(b);
    Int best_diff = std::abs(suma-sumb);
    bool changed = false;
    int best_pos_a = -1, best_pos_b = -1;
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)b.size(); ++j) {
            auto diff = std::abs(suma - sumb - 2 * a[i] + 2 * b[j]);
            if (diff < best_diff) {
                changed = true;
                best_pos_a = i;
                best_pos_b = j;
                best_diff = diff;
            }
        }
    }
    if (changed) {
        return {best_diff, 1, best_pos_a+1, best_pos_b+1};
    } else {
        return {best_diff, 0};
    }
}

std::vector<Int> step2(const std::vector<Int>& a, const std::vector<Int>& b) {
    Int suma = sum(a);
    Int sumb = sum(b);
    Int best_diff = std::abs(suma - sumb);
    std::vector<Int> sum_a, sum_b;
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = i + 1; j < (int)a.size(); ++j) {
            auto curr = suma - 2 * a[i] - 2 * a[j];
            sum_a.push_back(curr);
        }
    }
    for (int i = 0; i < (int)b.size(); ++i) {
        for (int j = i + 1; j < (int)b.size(); ++j) {
            auto curr = sumb - 2 * b[i] - 2 * b[j];
            sum_b.push_back(curr);
        }
    }
    std::sort(sum_a.begin(), sum_a.end());
    sum_a.erase(std::unique(sum_a.begin(), sum_a.end()), sum_a.end());
    
    std::sort(sum_b.begin(), sum_b.end());
    sum_b.erase(std::unique(sum_b.begin(), sum_b.end()), sum_b.end());
    
    
    bool changed = false;
    Int best1, best2;
    for (auto& it : sum_a) {
        auto jt = std::lower_bound(sum_b.begin(), sum_b.end(), it);
        if (jt != sum_b.end()) {
            assert(*jt >= it);
            auto diff = std::abs(it - *jt);
            if (diff < best_diff) {
                changed = true;
                best_diff = diff;
                best1 = it;
                best2 = *jt;
            }
        }
        if (jt != sum_b.begin()) {
            jt = std::prev(jt);
            assert(*jt < it);
            auto diff = std::abs(it - *jt);
            if (diff < best_diff) {
                changed = true;
                best_diff = diff;
                best1 = it;
                best2 = *jt;
            }
        }
    }
    if (changed) {
        std::pair<int, int> p1{-1, -1}, p2{-1, -1};
        for (int i = 0; i < (int)a.size(); ++i) {
            for (int j = i + 1; j < (int)a.size(); ++j) {
                auto curr = suma - 2 * a[i] - 2 * a[j];
                if (curr == best1) {
                    p1 = {i, j};
                    break;
                }
            }
        }
        for (int i = 0; i < (int)b.size(); ++i) {
            for (int j = i + 1; j < (int)b.size(); ++j) {
                auto curr = sumb - 2 * b[i] - 2 * b[j];
                if (curr == best2) {
                    p2 = {i, j};
                    break;
                }
            }
        }
        return {best_diff, 2, p1.first+1, p2.first+1, p1.second+1, p2.second+1};
    } else {
        return {best_diff, 0};
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    int na, nb;
    std::cin >> na;
    std::vector<Int> a(na);
    for (auto& it : a) std::cin >> it;
    std::cin >> nb;
    std::vector<Int> b(nb);
    for (auto& it : b) std::cin >> it;
    
    auto answ0 = std::vector<Int>{std::abs(sum(a)-sum(b)), 0};
    auto answ1 = step1(a, b);
    auto answ2 = step2(a, b);
    auto answ = answ0;
    if (answ0.front() <= answ1.front()) {
        if (answ0.front() <= answ2.front()) {
            answ = answ0;
        } else {
            answ = answ2;
        }
    } else {
        if (answ1.front() <= answ2.front()) {
            answ = answ1;
        } else {
            answ = answ2;
        }
    }
    
    std::cout << answ[0] << std::endl << answ[1] << std::endl;
    if (answ[1] >= 1) {
        std::cout << answ[2] << " " << answ[3] << std::endl;
    }
    if (answ[1] >= 2) {
        std::cout << answ[4] << " " << answ[5] << std::endl;
    }
    
    return 0;
}