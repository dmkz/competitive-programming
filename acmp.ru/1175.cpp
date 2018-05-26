#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

struct DataStruct {
    std::vector<int> arr, min;
    
    const int GSIZE = 258;
    
    DataStruct(int size = 0, int item = 0) {
        arr.assign(size, item);
        min.assign(size / GSIZE+1, item);
    }
    
    void set(int p, int v) {
        arr[p] = v;
        const int g = p / GSIZE;
        min[g] = v;
        const int begin = g * GSIZE;
        const int after = std::min(begin + GSIZE, (int)arr.size());
        for (int i = begin; i < after; ++i) {
            min[g] = std::min(arr[i], min[g]);
        }
    }
    
    int get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        int answ = INT_MAX;
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                answ = std::min(answ, arr[i]);
            }
        } else {
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                answ = std::min(answ, arr[i]);
            }
            for (int g = gl+1; g < gr; ++g) {
                answ = std::min(answ, min[g]);
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                answ = std::min(answ, arr[i]);
            }
        }
        return answ;
    }
    
};

int main() {
    int n; 
    scanf("%d", &n);
    DataStruct ds(n, 0);
    for (int i = 0; i < n; ++i) {
        int value;
        scanf("%d", &value);
        ds.set(i, value);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        --l, --r;
        printf("%d ", ds.get(l, r));
    }
    return 0;
}