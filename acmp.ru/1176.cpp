#include <stdio.h>
#include <vector>
#include <climits>
#include <cassert>

int log2[1+300];

void prepare() {
    for (int i = 2; i <= 300; ++i) {
        log2[i] = log2[i / 2] + 1;
    }
}

struct SparseTable {
    std::vector<std::vector<int>> data;
    
    SparseTable(const std::vector<int>& arr) {
        const int n = (int)arr.size();
        data.reserve(log2[n]+1);
        data.push_back(arr);
        for (int pow = 1, len = 1; 2 * len <= n; ++pow, len *= 2) {
            data.push_back(std::vector<int>(n-2*len+1));
            for (int pos = 0; pos + 2 * len <= n; ++pos) {
                data[pow][pos] = std::min(
                    data[pow-1][pos], data[pow-1][pos+len]
                );
            }
        }
    }
    
    int get(int l, int r) {
        const int level = log2[r-l+1];
        return std::min(data[level][l], data[level][r-(1 << level)+1]);
    }
};

int main() {
    prepare();
    int n, m, q; 
    scanf("%d %d %d", &n, &m, &q);
    std::vector<SparseTable> ds;
    ds.reserve(n);
    for (int i = 0; i < n; ++i) {
        std::vector<int> temp(m);
        for (auto& it : temp) {
            scanf("%d", &it);
        }
        ds.push_back(temp);
    }
    while (q--) {
        int i1, j1, i2, j2;
        scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
        --i1, --j1, --i2, --j2;
        int min = ds[i1].get(j1, j2);
        for (int i = i1+1; i <= i2; ++i) {
            min = std::min(min, ds[i].get(j1, j2));
        }
        printf("%d\n", min);
    }
    return 0;
}