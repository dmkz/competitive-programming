/*
    Problem: 846D. Monitor
    
    Solution: binary search, prefix sums, O(log(MAX) * n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct Query {
    int row, col, time;
};

bool operator<(const Query& a, const Query& b) {
    return a.time < b.time || (a.time == b.time && (a.row < b.row || (a.row == b.row && a.col < b.col)));
}

bool solve(int nRows, int nCols, int k, const std::vector<Query>& queries, int time) {
// check on possibility getting square k*k in time interval [0, time):    
    vvi arr(1+nRows, vi(1+nCols));
    for (auto& q : queries) {
        if (q.time >= time) {
            break;
        }
        arr[q.row][q.col]++;
    }
    vvi sum(1+nRows, vi(1+nCols));
    for (int i = 1; i <= nRows; ++i) {
        for (int j = 1; j <= nCols; ++j) {
            sum[i][j] = arr[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }
    for (int i = 1; i+k-1 <= nRows; ++i) {
        for (int j = 1; j+k-1 <= nCols; ++j) {
            int s = sum[i+k-1][j+k-1] - sum[i-1][j+k-1] - sum[i+k-1][j-1] + sum[i-1][j-1];
            if (s == k * k) {
                return true;
            }
        }
    }
    return false;
}
const int MAX = (int)1e9;
int main() {
    int nRows, nCols, side, nQueries;
    scanf("%d %d %d %d", &nRows, &nCols, &side, &nQueries);
    std::vector<Query> queries(nQueries);
    for (int i = 0; i < nQueries; ++i) {
        int row, col, time;
        scanf("%d %d %d", &row, &col, &time);
        queries[i] = Query{row, col, time};
    }
    std::sort(queries.begin(), queries.end());
    // Binary search on answer:
    int low = -1, high = MAX+2;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (solve(nRows, nCols, side, queries, mid)) {
            high = mid;
        } else low = mid;
    }
    if (low > MAX) low = -1;
    printf("%d", low);
    return 0;
}