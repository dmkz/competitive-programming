#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <vector>
#include <algorithm>

struct Record {
    int sum, left, right;
};

Record combine(const Record& a, const Record& b) {
    return Record{a.sum + b.sum + a.left * b.right, a.left, b.right};
}

bool operator<(const Record& a, const Record& b) {
    return a.sum < b.sum;
}

int main() {
    int n; scanf("%d", &n);
    
    const int INF = (int)1e9+1;
    std::vector<std::vector<Record>> min(n, std::vector<Record>(n, Record{INF, 0, 0})); // min[i][j] = min on segment from i to j
    
    for (int i = 0; i < n; ++i) {
        int m, k; 
        scanf("%d %d", &m, &k);
        min[i][i] = Record{0, m, k};
    }    
    
    for (int len = 2; len <= n; ++len) {
        for (int i = 0, j = len-1; j < n; ++i, ++j) {
            for (int k = i; k < j; ++k) {
                min[i][j] = std::min(min[i][j], combine(min[i][k], min[k+1][j]));
            }
        }
    }
    
    printf("%d\n", min[0][n-1].sum);   
    
    return 0;
}