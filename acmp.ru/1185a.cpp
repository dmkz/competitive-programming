#include <stdio.h>
#include <vector>
#include <cassert>

struct DataStruct {
    std::vector<int> arr, max, add;
    
    const int GSIZE = 64;
    
    DataStruct(int size = 0, int item = 0) {
        arr.assign(size, item);
        max.assign((size+GSIZE-1) / GSIZE, item);
        add.assign((size+GSIZE-1) / GSIZE, 0);
    }
    
    void push(int g) {
        if (add[g] == 0) return;
        const int value = add[g];
        add[g] = 0;
        const int after = std::min((g+1)*GSIZE, (int)arr.size());
        
        for (int i = g * GSIZE; i < after; ++i) {
            arr[i] += value;
        }
        max[g] += value;
    }
    
    void inc(int l, int r, int v) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        if (gl == gr) {
            push(gl);
            for (int i = l; i <= r; ++i) {
                arr[i] += v;
                max[gl] = std::max(max[gl], arr[i]);
            }
        } else {
            push(gl); assert(add[gl] == 0);
            push(gr); assert(add[gr] == 0);
            for (int i = l, limit = (gl+1)*GSIZE; i < limit; ++i) {
                arr[i] += v;
                max[gl] = std::max(arr[i], max[gl]);
            }
            
            for (int g = gl+1; g < gr; ++g) {
                add[g] += v;
            }
            
            for (int i = gr * GSIZE; i <= r; ++i) {
                arr[i] += v;
                max[gr] = std::max(arr[i], max[gr]);
            }
        }
    }
    
    int get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        int answ = arr[l];
        if (gl == gr) {
            push(gl);
            for (int i = l; i <= r; ++i) {
                answ = std::max(answ, arr[i]);
            }
        } else {
            push(gl);
            push(gr);
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                answ = std::max(answ, arr[i]);
            }
            for (int g = gl+1; g < gr; ++g) {
                answ = std::max(answ, max[g]+add[g]);
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                answ = std::max(answ, arr[i]);
            }
        }
        return answ;
    }
};

int main() {
    int n, limit, q; scanf("%d %d %d", &n, &limit, &q);
    DataStruct ds(n, 0);
    while (q--) {
        int l, r; scanf("%d %d", &l, &r); r--;
        if (ds.get(l, r) == limit) {
            printf("No\n");
        } else {
            ds.inc(l, r, 1);
            printf("Yes\n");
        }
    }
    return 0;
}