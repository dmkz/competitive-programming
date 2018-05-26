#include <stdio.h>
#include <vector>
#include <cassert>

struct DataStruct {
    std::vector<int> arr, max, actual;
    
    const int GSIZE = 256;
    
    DataStruct(int size = 0, int item = 0) {
        arr.assign(size, item);
        max.assign((size+GSIZE-1) / GSIZE, item);
        actual.assign((size+GSIZE-1) / GSIZE, true);
    }
    
    void update_group(int g) {
        if (actual[g]) return;
        actual[g] = true;
        const int begin = g * GSIZE;
        const int after = std::min(begin+GSIZE, (int)arr.size());
        int value = arr[begin];
        for (int i = begin+1; i < after; ++i) {
            value = std::max(value, arr[i]);
        }
        max[g] = value;
    }
    
    void set(int p, int v) {
        const int g = p / GSIZE;
        arr[p] = v;
        actual[g] = false;
    }
    
    int get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        int answ = arr[l];
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                answ = std::max(answ, arr[i]);
            }
        } else {
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                answ = std::max(answ, arr[i]);
            }
            for (int g = gl+1; g < gr; ++g) {
                if (!actual[g]) update_group(g);
                answ = std::max(answ, max[g]);
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                answ = std::max(answ, arr[i]);
            }
        }
        return answ;
    }
    
};


int main() {
    int n; scanf("%d", &n);
    DataStruct ds(n, 0);
    for (int i = 0; i < n; ++i) {
        int value; scanf("%d", &value);
        ds.set(i, value);
    }
    int q; scanf("%d", &q);
    while (q--) {
        char t; int l, r;
        scanf(" %c %d %d", &t, &l, &r);
        if (t == 'm') {
            printf("%d ", ds.get(l-1, r-1));
        } else {
            assert(t == 'u');
            ds.set(l-1, r);
        }
    }
    return 0;
}