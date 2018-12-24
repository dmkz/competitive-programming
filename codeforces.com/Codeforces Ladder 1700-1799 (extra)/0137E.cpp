/*
    Problem: 137E. Last Chance
    
    Solution: Sqrt-Decomposition, lower bound, O(n sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <tuple>

typedef std::pair<int,int> pii;
typedef std::vector<int> vi;

const int INF = (int)1e9+7;

struct SqrtDecomposition {
    
    static const int gsize = 256;
    
    vi arr, grAdd, grMax, grBegin, grAfter;
    
    SqrtDecomposition(const vi &arr_) : arr(arr_) {
        const int nGroups = ((int)arr.size() + gsize - 1) / gsize;
        grAdd.assign(nGroups,    0);
        grMax.assign(nGroups, -INF);
        grBegin.assign(nGroups,    0);
        grAfter.assign(nGroups,    0);
        for (int g = 0; g < nGroups; ++g) {
            const int begin = grBegin[g] = g * gsize;
            const int after = grAfter[g] = std::min((g+1)*gsize, (int)arr.size());
            int &max = grMax[g];
            for (int i = begin; i < after; ++i) {
                max = std::max(max, arr[i]);
            }
        }
    }
    
    void push(int g) {
        int &add = grAdd[g], &max = grMax[g];
        const int begin = grBegin[g];
        const int after = grAfter[g];
        max = -INF;
        for (int i = begin; i < after; ++i) {
            arr[i] += add;
            max = std::max(max, arr[i]);
        }
        add = 0;
    }
    
    void inc(int lt, int rt, int value) {
        const int gl = lt / gsize;
        const int gr = rt / gsize;
        if (gl == gr) {
            push(gl);
            int &max = grMax[gl];
            for (int i = lt; i <= rt; ++i) {
                arr[i] += value;
                max = std::max(max, arr[i]);
            }
        } else {
            push(gl);
            push(gr);

            for (int i = lt; i < grAfter[gl]; ++i) {
                arr[i] += value;
            }
            
            for (int g = gl+1; g < gr; ++g) {
                grAdd[g] += value;
            }
            
            for (int i = grBegin[gr]; i <= rt; ++i) {
                arr[i] += value;
            }
            
            push(gl);
            push(gr);
        }
    }
    
    int last_equal_or_greater(int lt, int rt, int x) {
        const int gl = lt / gsize;
        const int gr = rt / gsize;
        if (gl == gr) {
            push(gl);
            for (int i = rt; i >= lt; --i) {
                if (arr[i] >= x) {
                    return i;
                }
            }
            return lt-1;
        } else {
            push(gl);
            push(gr);
            for (int i = rt; i >= grBegin[gr]; --i) {
                if (arr[i] >= x) {
                    return i;
                }
            }
            for (int g = gr-1; g > gl; --g) {
                if (grMax[g] + grAdd[g] >= x) {
                    push(g);
                    for (int i = grAfter[g]-1; i >= grBegin[g]; --i) {
                        if (arr[i] >= x) {
                            return i;
                        }
                    }
                    assert(false);
                }
            }
            for (int i = grAfter[gl]-1; i >= lt; --i) {
                if (arr[i] >= x) {
                    return i;
                }
            }
            return lt-1;
        }
    }
};

bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

pii solve(const std::string& s) {
    const int n = (int)s.size();
    vi val(n);
    val[0] = is_vowel(s[0]) ? -1 : 2;
    for (int i = 1; i < n; ++i) {
        val[i] = val[i-1] + (is_vowel(s[i]) ? -1 : 2);
    }
    SqrtDecomposition ds(val);
    int best = 0, cnt = 0;
    for (int i = 0; i < n; ++i) {
        int pos = ds.last_equal_or_greater(i, n-1, 0);
        if (best < pos + 1 - i) {
            best = pos + 1 - i;
            cnt = 0;
        }
        if (best == pos + 1 - i) {
            cnt++;
        }
        ds.inc(i, n-1, -(is_vowel(s[i]) ? -1 : 2));
    }
    return pii(best, cnt);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s;
    while (std::cin >> s) {
        for (auto &it : s) {
            it = ('A' <= it && it <= 'Z') ? char('a' + it - 'A') : it;
        }
        int len, cnt;
        std::tie(len, cnt) = solve(s);
        if (len == 0) {
            std::cout << "No solution" << std::endl;
        } else {
            std::cout << len << ' ' << cnt << std::endl;
        }
    }
    return 0;
}