/*
    Problem: 1090. In the Army Now
    
    Solution: Fenwick, O(k*n*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <cassert>
#include <cstdint>

struct Fenwick {

    std::vector<int> data;
    
    Fenwick(int size) : data(size, 0) { }

    void inc(int p, int value = 1) {
        while (p < (int)data.size()) {
            data[p] += value;
            p |= p+1;
        }
    }
    
    int get(int r) const {
        int answ = 0;
        while (r >= 0) {
            answ += data[r];
            r = (r & (r+1)) - 1;
        }
        return answ;
    }
};


int main() {
    int nCols, nRows;
    scanf("%d %d", &nCols, &nRows);
    int64_t max = -1;
    int row = 0;
    for (int r = 1; r <= nRows; ++r) {
        Fenwick fw(1+nCols);
        int64_t sum = 0;
        for (int i = 0; i < nCols; ++i) {
            int value; scanf("%d", &value);
            value = nCols+1-value;
            sum += fw.get(value);
            fw.inc(value);
        }
        if (sum > max) {
            max = sum;
            row = r;
        }
    }
    assert(row != 0);
    printf("%d\n", row);
    return 0;
}