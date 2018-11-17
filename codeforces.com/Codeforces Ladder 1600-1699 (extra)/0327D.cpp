/*
    Problem: 327D. Block Tower
    
    Solution: graphs, dfs, constructive, O(n * m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cassert>

typedef std::vector<char> vc;
typedef std::vector<vc> vvc;

const char WALL = '#', EMPTY = '.', RED = 'R', BLUE = 'B';

struct Triple {
    char type; int i, j;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nRows, nCols;
    while (std::cin >> nRows >> nCols) {
        vvc arr(1+nRows+1, vc(1+nCols+1, '#'));
        for (int i = 1; i <= nRows; ++i) {
            std::string s; std::cin >> s;
            for (int j = 1; j <= nCols; ++j) {
                arr[i][j] = s[j-1];
            }
        }
        std::vector<Triple> answer;
        std::function<void(int,int)> dfs = [&](int i, int j) {
            assert(arr[i][j] == EMPTY);
            answer.push_back(Triple{'B', i, j});
            arr[i][j] = 'B';
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di * di + dj * dj != 1) continue;
                    int ni = i + di;
                    int nj = j + dj;
                    if (arr[ni][nj] == EMPTY) {
                        dfs(ni, nj);
                    }
                }
            }
            bool flag = false;
            for (int di = -1; !flag && di <= 1; ++di) {
                for (int dj = -1; !flag && dj <= 1; ++dj) {
                    if (di * di + dj * dj != 1) continue;
                    int ni = i + di;
                    int nj = j + dj;
                    if (arr[ni][nj] == BLUE) {
                        flag = true;
                    }
                }
            }
            if (flag) {
                answer.push_back(Triple{'D', i, j});
                answer.push_back(Triple{'R', i, j});
                arr[i][j] = RED;
            }
        };
        for (int i = 1; i <= nRows; ++i) {
            for (int j = 1; j <= nCols; ++j) {
                if (arr[i][j] == EMPTY) { dfs(i, j); }
            }
        }
        std::cout << answer.size() << "\n";
        for (const auto &t : answer) {
            std::cout << t.type << ' ' << t.i << ' ' << t.j << "\n";
        }
    }
    return 0;
}