#include <stdio.h>
#include <vector>
#include <climits>
#include <cassert>
#include <array>

int log2[1+100000];

void prepare() {
    for (int i = 2; i <= 100000; ++i) {
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
                data[pow][pos] = std::max(
                    data[pow-1][pos], data[pow-1][pos+len]
                );
            }
        }
    }
    
    int get(int l, int r) {
        const int level = log2[r-l+1];
        return std::max(data[level][l], data[level][r-(1 << level)+1]);
    }
};

int main() {
    prepare();
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) {
        scanf("%d", &it);
    }
    SparseTable st(arr);    
    int nQueries;
    scanf("%d", &nQueries);
    while (nQueries--) {
        int l, r;
        scanf("%d %d", &l, &r);
        --l, --r;
        printf("%d ", st.get(l, r));
    }
    return 0;
}