/*
    Problem: 540C. Ice Cave
    
    Solution: bfs, grid graph, O(n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <string>
#include <queue>

typedef std::vector<char> vc;
typedef std::vector<bool> vb;
typedef std::vector<int> vi;
typedef std::vector<vc> vvc;
typedef std::vector<vb> vvb;
typedef std::vector<vi> vvi;

int main() {
    int nRows, nCols;
    while (std::cin >> nRows >> nCols) {
        vvc field(1+nRows+1, vc(1+nCols+1, 'X'));
        vvi nDot(1+nRows+1, vi(1+nCols+1,  0));
        vvi dist(1+nRows+1, vi(1+nCols+1, -1));
        for (int r = 1; r <= nRows; ++r) {
            std::string s; std::cin >> s;
            for (int c = 1; c <= nCols; ++c) {
                field[r][c] = s[c-1];
            }
        }
        for (int r = 1; r <= nRows; ++r) {
            for (int c = 1; c <= nCols; ++c) {
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        nDot[r][c] += (dr * dr + dc * dc == 1 && field[r+dr][c+dc] == '.');
                    }
                }
            }
        }
        int sr, sc, tr, tc;
        std::cin >> sr >> sc >> tr >> tc;
        std::queue<int> queue;
        queue.push((sr << 10) + sc);
        dist[sr][sc] = 0;
        while (!queue.empty()) {
            int r = queue.front() >> 10;
            int c = queue.front() & ((1 << 10) - 1);
            queue.pop();
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr * dr + dc * dc != 1 || dist[r+dr][c+dc] != -1) continue;
                    dist[r+dr][c+dc] = dist[r][c]+1;
                    if (field[r+dr][c+dc] == '.') {
                        queue.push(((r + dr) << 10)+(c+dc));
                    }
                }
            }
        }
        if (sr == tr && sc == tc) {
            std::cout << (nDot[sr][sc] > 0 ? "YES" : "NO") << std::endl;
            continue;
        }
        if (dist[tr][tc] == -1) {
            std::cout << "NO" << std::endl;
            continue;
        }
        if (field[tr][tc] == 'X') {
            std::cout << "YES" << std::endl;
            continue;
        }
        if (dist[tr][tc] == 1 && nDot[tr][tc] > 0) {
            std::cout << "YES" << std::endl;
            continue;
        }
        if (nDot[tr][tc] >= 2) {
            std::cout << "YES" << std::endl;
            continue;
        }
        std::cout << "NO" << std::endl;
    }
    return 0;
}