/*
    Решение двумерным ДП:
        
        1. Предподсчитаем pref[i][j] = len - длина совпадающего суффикса на префиксе a[0..i] и b[0..j]
        
        2. Предподсчитаем suff[i][j] = len - длина совпадающего префикса на суффиксе a[i..n) и b[i..n)
        
        3. Предподсчитаем best_pref[i][j] = {pos, len} - наибольшая общая подстрока на префиксе a[0..i] и b[0..j]
        
        4. Предподсчитаем best_suff[i][j] = {pos, len} - наибольшая общая подстрока на суффиксе a[i..n) и b[i..n)
        
        5. Переберем позиции i и j и выберем максимальную пару общих строк на префиксе + суффиксе одновременно
    
    Асимптотика O(n^2) по времени и O(n^2) по памяти.
    
    Возможно, шаги 1 и 3, а также шаги 2 и 4 можно было объединить, но так нагляднее.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <cstdint>

typedef int16_t Int;

struct Pair {
    Int pos, len;
};

inline bool operator<(const Pair& a, const Pair& b) {
    return a.len < b.len || (a.len == b.len && a.pos > b.pos);
}

inline bool operator>(const Pair& a, const Pair& b) {
    return b < a;
}

inline bool operator==(const Pair& a, const Pair& b) {
    return a.len == b.len && a.pos == b.pos;
}

typedef std::vector<Pair> Vector;
typedef std::vector<Vector> Matrix;

void solve(const std::string& a, const std::string& b, std::string& r1, std::string& r2) {
    const Int n1 = a.size(), n2 = b.size();
    r1.clear(); r2.clear();
    // Считаем наибольшую общую подстроку на префиксе, совпадающую с суффиксом:
    std::vector<std::vector<Int>> pref(n1, std::vector<Int>(n2));
    for (Int i = 0; i < n1; ++i) {
        for (Int j = 0; j < n2; ++j) {
            if (a[i] == b[j]) {
                pref[i][j] = (i > 0 && j > 0 ? pref[i-1][j-1] : 0) + 1;
            } else {
                pref[i][j] = 0;
            }
        }
    }
    // Считаем наибольшую общую подстроку на суффиксе, совпадающую с префиксом:
    std::vector<std::vector<Int>> suff(n1, std::vector<Int>(n2));
    for (Int i = n1-1; i >= 0; --i) {
        for (Int j = n2-1; j >= 0; --j) {
            if (a[i] == b[j]) {
                suff[i][j] = (i+1 < n1 && j+1 < n2 ? suff[i+1][j+1] : 0) + 1;
            } else {
                suff[i][j] = 0;
            }
        }
    }
    // Считаем наибольшую общую подстроку на префиксе:
    Matrix best_pref(n1, Vector(n2, Pair{-1, 0}));
    for (Int i = 0; i < n1; ++i) {
        for (Int j = 0; j < n2; ++j) {
            if (i == 0 && j == 0) {
                best_pref[i][j] = Pair{Int(i-pref[i][j]+1), pref[i][j]};
            } else if (i == 0) {
                best_pref[i][j] = std::max(
                    best_pref[i][j-1], Pair{Int(i-pref[i][j]+1), pref[i][j]}
                );
            } else if (j == 0) {
                best_pref[i][j] = std::max(
                    best_pref[i-1][j], Pair{Int(i-pref[i][j]+1), pref[i][j]}
                );
            } else {
                best_pref[i][j] = std::max({
                    best_pref[i-1][j], best_pref[i][j-1], Pair{Int(i-pref[i][j]+1), pref[i][j]}
                });
            }
        }
    }
    // Считаем наибольшую общую подстроку на суффиксе:
    Matrix best_suff(n1, Vector(n2, Pair{-1, 0}));
    for (Int i = n1-1; i >= 0; --i) {
        for (Int j = n2-1; j >= 0; --j) {
            if (i == n1-1 && j == n2-1) {
                best_suff[i][j] = Pair{i, suff[i][j]};
            } else if (i == n1-1) {
                best_suff[i][j] = std::max(
                    best_suff[i][j+1], Pair{i, suff[i][j]}
                );
            } else if (j == n2-1) {
                best_suff[i][j] = std::max(
                    best_suff[i+1][j], Pair{i, suff[i][j]}
                );
            } else {
                best_suff[i][j] = std::max({
                    best_suff[i+1][j], best_suff[i][j+1], Pair{i, suff[i][j]}
                });
            }
        }
    }
    // Находим ответ:
    Pair p1{-1, 0}, p2{-1, 0}; Int best_len = 0;
    for (Int i = 0; i < n1; ++i) {
        for (Int j = 0; j < n2; ++j) {
            // Префикс [0, i) и Суффикс [i, n)
            if (i > 0 && j > 0) {
                Int sum_len = best_pref[i-1][j-1].len + best_suff[i][j].len;
                if (sum_len > best_len) {
                    best_len = sum_len;
                    p1 = best_pref[i-1][j-1];
                    p2 = best_suff[i][j];
                }
            } else if (i == 0 && j == 0) {
                Int sum_len = best_suff[i][j].len;
                if (sum_len > best_len) {
                    best_len = sum_len;
                    p2 = best_suff[i][j];
                    p1 = Pair{-1, 0};
                }
            }
        }
    }
    if (p1.pos != -1) {
        r1 = a.substr(p1.pos, p1.len);
    }
    if (p2.pos != -1) {
        r2 = a.substr(p2.pos, p2.len);
    }
}

int main() {
    char buf[2000+1];
    scanf("%2000s", buf);
    std::string a(buf);
    scanf("%2000s", buf);
    std::string b(buf), r1, r2;
    solve(a, b, r1, r2);
    if (r1.empty()) {
        std::swap(r1, r2);
    }
    if (r1.empty()) {
        return 0;
    }
    if (!r1.empty()) {
        printf("%s\n", r1.c_str());
    }
    if (!r2.empty()) {
        printf("%s\n", r2.c_str());
    }
    return 0;
}