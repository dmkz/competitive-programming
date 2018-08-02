/*
    Problem: 691E. Xor-sequences
    
    Solution: Sparse Table, dynamic programming, O(n^3 log(k))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cassert>

typedef long long ll;

const int mod = (int)1e9+7;

inline int add(int a, int b) {
    return (a += b) >= mod ? a - mod : a;
}

inline int mul(int a, int b) {
    return int(ll(a) * b % mod);
}

int main() {
    int n; ll need; std::cin >> n >> need;
    
    std::vector<ll> a(n);
    for (auto& it : a) std::cin >> it;
    std::sort(a.begin(), a.end());
    
    std::vector<ll> len{1,2};
    while (len.back() <= need) {
        len.push_back(2*len.back()-1);
    }
    
    static int count[100][100][100]; // lens: 1, 2, 3, 5, 9, ..., 2*len-1, ...
    
    // Init count for sequences with len = 1:
    for (int i = 0; i < n; ++i) {
        count[0][i][i] = 1;
    }
    
    // Calculate count for sequences with len = 2:
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            count[1][i][j] = (__builtin_popcountll(a[i] ^ a[j]) % 3 == 0);
        }
    }
    
    // Calculate count for other lens:
    for (int lvl = 2; lvl < (int)len.size(); ++lvl) {
        for (int l = 0; l < n; ++l) {
            for (int m = 0; m < n; ++m) {
                for (int r = 0; r < n; ++r) {
                    count[lvl][l][r] = add(count[lvl][l][r], mul(count[lvl-1][l][m], count[lvl-1][m][r]));
                }
            }
        }
    }
    
    // Function for answer to query:
    std::function<int(ll)> query = [&](ll k) {
        assert(k > 0);
        // Init answer by table for first len not greater then k:
        std::vector<std::vector<int>> answ(n, std::vector<int>(n));
        auto temp = answ;
        int pos = (int)len.size()-1;
        while (pos >= 0 && len[pos] > k) --pos;
        ll cur = len[pos];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                temp[i][j] = count[pos][i][j];
            }
        }
        answ.swap(temp);
        // Combine answer's table with tables for other lens:
        while (cur < k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    temp[i][j] = 0;
                }
            }
            while (pos >= 0 && cur + len[pos] - 1 > k) --pos;
            cur = cur + len[pos] - 1;
            for (int l = 0; l < n; ++l) {
                for (int m = 0; m < n; ++m) {
                    for (int r = 0; r < n; ++r) {
                        temp[l][r] = add(temp[l][r], mul(answ[l][m], count[pos][m][r]));
                    }
                }
            }
            answ.swap(temp);
        }
        assert(cur == k);
        // Calculate answer:
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                res = add(res, answ[i][j]);
            }
        }
        return res;
    };
    
    std::cout << query(need);
    return 0;
}