/*
    "Перестановки - 3": динамическое программирование по профилю, O(n*2^(2n))
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

typedef long long ll;

int main() {
    int n, number, minGCD;
    scanf("%d %d %d", &n, &number, &minGCD);
    
    std::vector<int> a(n);
    for (auto& it : a) {
        scanf("%d", &it);
    }
    std::sort(a.begin(), a.end());
    
    std::vector<std::vector<bool>> is_pair(n, std::vector<bool>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            is_pair[i][j] = (i != j) && (gcd(a[i], a[j]) >= minGCD);
        }
    }
    
    std::vector<std::vector<ll>> count(n, std::vector<ll>(1 << n, 0));
    
    for (int code = 1; code < (1 << n); ++code) {
        for (int first = 0; first < n; ++first) {
            if (code == (1 << first)) {
                count[first][code] = 1;
            } else {
                int without_first = code & ~(1 << first);
                for (int second = 0; second < n; ++second) {
                    if (is_pair[first][second] && ((without_first >> second) & 1)) {
                        count[first][code] += count[second][without_first];
                    }
                }
            }
        }
    }
    
    std::vector<int> answ(n);
    int code = (1 << n) - 1;
    for (int pos = 0; pos < n; ++pos) {
        bool founded = false;
        for (int i = 0; i < n; ++i) {
            if (((code >> i) & 1) == 1 && (pos == 0 || is_pair[answ[pos-1]][i])) {
                if (count[i][code] >= number) {
                    answ[pos] = i;
                    code &= ~(1 << i);
                    founded = true;
                    break;
                } else {
                    number -= (int)count[i][code];
                }
            }
        }
        if (!founded) {
            printf("-1");
            return 0;
        }
    }
    
    for (auto& it : answ) {
        printf("%d ", a[it]);
    }
    
    
    return 0;
}