#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <iostream>

int main() {
    int nRows;
    scanf("%d", &nRows);
    std::vector<std::string> rows(2*nRows+1);
    for (int i = 0; i < nRows; ++i) {
        const int id = 2*i+1;
        int q; scanf("%d", &q);
        while (q--) {
            int w; scanf("%d", &w);
            rows[id] += '|' + std::string(w, ' ');
        }
        rows[id].push_back('|');
    }
    for (int i = 0; i <= nRows; ++i) {
        const int id = 2*i;
        int size = 0;
        if (i > 0) {
            size = std::max(size, (int)rows[id-1].size());
        }
        if (i < nRows) {
            size = std::max(size, (int)rows[id+1].size());
        }
        rows[id] = std::string(size, '-');
        for (int j = 0; j < size; ++j) {
            if (i > 0 && j < (int)rows[id-1].size() && rows[id-1][j] != ' ') {
                rows[id][j] = '+';
            }
            if (i < nRows && j < (int)rows[id+1].size() && rows[id+1][j] != ' ') {
                rows[id][j] = '+';
            }
        }
    }
    for (auto& r : rows) {
        printf("%s\n", r.c_str());
    }
    return 0;
}