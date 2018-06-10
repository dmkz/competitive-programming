#include <stdio.h>
#include <algorithm>
#include <cassert>
#include <vector>
#include <queue>

typedef std::vector<int> Vector;
typedef std::vector<Vector> Matrix;

struct Record {
    int row, col, side, sum;
};

bool operator>(const Record& a, const Record& b) {
    return a.sum > b.sum || (a.sum == b.sum && (a.side < b.side || (a.side == b.side && (a.row < b.row || (a.row == b.row && a.col < b.col)))));
}

bool operator<(const Record& a, const Record& b) {
    return b > a;
}

Record bfs(const int sr, const int sc, const int limit, const Matrix& arr) {
    const int nRows = (int)arr.size();
    const int nCols = (int)arr[0].size();
    
    std::queue<int> queue; 
    queue.push(sr*64+sc);
    
    Matrix dist(nRows, Vector(nCols, -1));
    dist[sr][sc] = 1;
    
    std::vector<int> sum(1+limit, 0);
    while (!queue.empty()) {
        const int r = queue.front() / 64;
        const int c = queue.front() % 64;
        queue.pop();
        assert(dist[r][c] > 0);
        sum[dist[r][c]] += arr[r][c];
        if (dist[r][c] == limit) {
            continue;
        }
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr * dr + dc * dc == 1) {
                    const int nr = r+dr;
                    const int nc = c+dc;
                    if (nr < 0 || nc < 0 || nr >= nRows || nc >= nCols) {
                        continue;
                    }
                    if (dist[nr][nc] == -1) {
                        dist[nr][nc] = dist[r][c] + 1;
                        queue.push(nr*64+nc);
                    }
                }
            }
        }
    }
    Record best{-1, -1, 0, int(-1e9)};
    int s = 0;
    for (int i = 1; i <= limit; ++i) {
        s += sum[i];
        best = std::max(best, Record{sr+1, sc+1, i, s});
    }
    return best;
}

int main() {
    int nRows, nCols, limit;
    scanf("%d %d %d", &nRows, &nCols, &limit);
    Matrix arr(nRows, Vector(nCols, 0));
    for (auto& row : arr) {
        for (auto& it : row) {
            scanf("%d", &it);
        }
    }
    Record best{-1,-1,0,int(-1e9)};
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            best = std::max(best, bfs(row, col, limit, arr));
        }
    }
    assert(best.row != -1);
    printf("%d %d %d %d", best.row, best.col, best.side, best.sum);
    return 0;
}