#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

struct DataStruct {
    std::vector<int> arr, max, pos;
    
    const int GSIZE = 258;
    
    DataStruct(int size = 0, int item = 0) {
        arr.assign(size, item);
        max.assign((size+GSIZE-1) / GSIZE, item);
        pos.assign((size+GSIZE-1) / GSIZE, 0);
        for (int g = 0; g < (int)pos.size(); ++g) {
            pos[g] = g * GSIZE;
        }
    }
    
    void set(int p, int v) {
        arr[p] = v;
        const int g = p / GSIZE;
        max[g] = v;
        pos[g] = p;
        const int begin = g * GSIZE;
        const int after = std::min(begin + GSIZE, (int)arr.size());
        for (int i = begin; i < after; ++i) {
            if (arr[i] > max[g]) {
                max[g] = arr[i];
                pos[g] = i;
            } else if (arr[i] == max[g]) {
                pos[g] = std::min(pos[g], i);
            }
        }
    }
    
    std::pair<int,int> get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        std::pair<int, int> answ = {arr[l], l};
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                if (arr[i] > answ.first) {
                    answ = {arr[i], i};
                }
            }
        } else {
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                if (arr[i] > answ.first) {
                    answ = {arr[i], i};
                }
            }
            for (int g = gl+1; g < gr; ++g) {
                if (max[g] > answ.first) {
                    answ = {max[g], pos[g]};
                }
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                if (arr[i] > answ.first) {
                    answ = {arr[i], i};
                }
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
        auto answ = ds.get(l, r);
        printf("%d %d\n", answ.first, answ.second+1);
    }
    return 0;
}