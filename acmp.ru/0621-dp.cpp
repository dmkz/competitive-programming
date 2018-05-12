#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

struct Record {
    int dist, count, row, col;
    
    Record(int dist = 500, int count = 2, int row = -1, int col = -1)
        : dist(dist)
        , count(count)
        , row(row)
        , col(col)
    { }
};

Record combine(const Record& a, const Record& b) {
    if (a.dist > b.dist) {
        return b;
    } else if (a.dist < b.dist) {
        return a;
    } else if (a.row == b.row && a.col == b.col) {
        return a;
    } else {
        return Record(a.dist, a.count+b.count, -1, -1);
    }
}

std::vector<std::vector<Record>> dp(int sr, int dr, int tr, int sc, int dc, int tc, const std::vector<std::vector<int>>& arr) {
    const int n = (int)arr.size();
    std::vector<std::vector<Record>> best(n, std::vector<Record>(n));
    for (int r = sr; r != tr; r += dr) {
        for (int c = sc; c != tc; c += dc) {
            if (arr[r][c] != 0) {
                best[r][c] = Record(0, 1, r, c);
                continue;
            }
            if (r != sr && c != sc) {
                best[r][c] = combine(best[r-dr][c], best[r][c-dc]);
            } else if (r != sr) {
                best[r][c] = best[r-dr][c];
            } else if (c != sc) {
                best[r][c] = best[r][c-dc];
            } else {
                continue;
            }
            best[r][c].dist++;
        }
    }
    return best;
}

std::vector<std::vector<int>> solve_dp(std::vector<std::vector<int>> arr) {
    const int n = (int)arr.size();
    // Walk from left-up corner:
    auto best_l_u = dp(  0,  1,  n,   0,  1,  n, arr);
    // Walk from left-down corner:
    auto best_l_d = dp(n-1, -1, -1,   0,  1,  n, arr);
    // Walk from right-up corner:
    auto best_r_u = dp(  0,  1,  n, n-1, -1, -1, arr);
    // Walk from right-down corner:
    auto best_r_d = dp(n-1, -1, -1, n-1, -1, -1, arr);
    // Combine all answers:
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] == 0) {
                auto best = combine(
                    combine(best_l_u[i][j], best_r_u[i][j]),
                    combine(best_l_d[i][j], best_r_d[i][j])
                );
                
                if (best.count == 1) {
                    arr[i][j] = arr[best.row][best.col];
                }
            }
        }
    }
    return arr;
}

int main() {
    int n; 
    scanf("%d", &n);
    
    std::vector<std::vector<int>> arr(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }
    auto arr1 = solve_dp(arr);
    for (auto& row : arr1) {
        for (auto& it : row) {
            printf("%d ", it);
        }
        printf("\n");
    }
    return 0;
}