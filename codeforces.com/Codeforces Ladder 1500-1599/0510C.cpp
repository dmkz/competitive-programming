/*
    Problem: 510C. Fox And Names
    Solution: dfs, graphs, sorting
*/
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <cassert>

int main() {
    int n, m = 0; std::cin >> n;
    std::vector<std::string> arr(n);
    for (auto& it : arr) {
        std::cin >> it;
        for (auto& c : it) c = char(c - 'a' + 1);
        m = std::max(m, (int)it.size());
    }
    for (auto& it : arr) {
        while ((int)it.size() < m) {
            it.push_back(0);
        }
    }
    
    const int UNDEF = -2;
    const int LESS = -1;
    const int EQUAL = 0;
    const int GREATER = 1;
    
    std::vector<std::vector<int>> compare(27, std::vector<int>(27, UNDEF));
    for (int i = 0; i < 27; ++i) compare[i][i] = EQUAL;
    std::function<void(int,int,int)> visit = [&](int begin, const int after, const int col) {
        if (col == m || begin >= after) return;
        // Проходим по всем позициям, сравнивая начальные символы:
        for (int r1 = begin; r1 < after; ++r1) {
            int r2 = r1;
            while (r2 < after && arr[r1][col] == arr[r2][col]) ++r2;
            while (r2 < after) {
                auto c1 = arr[r1][col];
                auto c2 = arr[r2][col];
                if (compare[c1][c2] == UNDEF) {
                    compare[c1][c2] = LESS;
                    compare[c2][c1] = GREATER;
                } else if (compare[c1][c2] != LESS) {
                    std::cout << "Impossible";
                    std::exit(0);
                }
                ++r2;
            }
        }
        // Рекурсивные вызовы от равных на текущей итерации подстрок:
        while (begin < after) {
            int r = begin;
            while (r < after && arr[r][col] == arr[begin][col]) ++r;
            visit(begin, r, col+1);
            begin = r;
        }
    };
    // Запуск dfs:
    visit(0, n, 0);
    // Доведение таблицы сравнений до полной:
    for (int step = 0; step < 27; ++step) {
        for (int i = 0; i < 27; ++i) {
            for (int j = 0; j < 27; ++j) {
                for (int k = 0; k < 27; ++k) {
                    if (compare[i][j] == LESS && compare[j][k] == LESS) {
                        if (compare[i][k] == GREATER) {
                            std::cout << "Impossible";
                            return 0;
                        }
                        compare[i][k] = LESS;
                    }
                }
            }
        }
    }
    // Формирование подстановки букв:
    std::vector<int> p(27, -1);
    std::vector<int> to(27, -1);
    std::vector<bool> used(27,0);
    for (int k = 0; k < 27; ++k) {
        int imin = -1;
        for (int i = 0; i < 27; ++i) {
            if (used[i]) continue;
            bool flag = true;
            for (int j = 0; j < 27; ++j) {
                if (j == i) continue;
                if (compare[i][j] == GREATER) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                imin = i;
                break;
            }
        }
        if (imin == -1) break;
        p[k] = imin;
        to[imin] = k;
        for (int i = 0; i < 27; ++i) {
            compare[i][imin] = compare[imin][i] = UNDEF;
        }
        used[imin] = true;
    }
    if (p[0] != 0) {
        std::cout << "Impossible";
        return 0;
    }
    for (int i = 0; i < 27; ++i) {
        if (p[i] == -1) p[i] = i;
    }
    // Вывод ответа:
    for (int i = 1; i <= 26; ++i) {
        std::cout << char(p[i]+'a'-1);
    }
    return 0;
}