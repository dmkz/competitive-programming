#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

struct DataStruct {
    std::vector<int> arr, count;
    
    const int GSIZE = 128;
    
    DataStruct(int size = 0, int item = 0) {
        arr.assign(size, item);
        count.assign((size+GSIZE-1), 0);
        for (int g = 0; g < (int)count.size(); ++g) {
            const int begin = g * GSIZE;
            const int after = std::min(begin+GSIZE, size);
            for (int i = begin; i < after; ++i) {
                count[g] += (arr[i] == 0);
            }
        }
    }
    
    void set(int p, int v) {
        const int g = p / GSIZE;
        if (arr[p] == 0) {
            count[g]--;
        }
        arr[p] = v;
        if (arr[p] == 0) {
            count[g]++;
        }
    }
    
    int get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        int answ = 0;
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                answ += (arr[i] == 0);
            }
        } else {
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                answ += (arr[i] == 0);
            }
            for (int g = gl+1; g < gr; ++g) {
                answ += count[g];
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                answ += (arr[i] == 0);
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