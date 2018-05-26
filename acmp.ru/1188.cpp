#include <stdio.h>
#include <vector>
#include <cassert>

typedef long long ll;

struct SqrtDecomposition {
    std::vector<ll> arr, extra;
    
    SqrtDecomposition(int size, int element) {
        arr.assign(size, element);
        extra.assign((size+GSIZE-1) / GSIZE, 0);
    }
    
    const int GSIZE = 256;
    
    void add(int l, int r, int x) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                arr[i] += x;
            }
        } else {
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                arr[i] += x;
            }
            for (int g = gl+1; g < gr; ++g) {
                extra[g] += x;
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                arr[i] += x;
            }
        }
    }
    
    ll get(int pos) {
        return arr[pos] + extra[pos / GSIZE];
    }
};

int main() {
    int n; scanf("%d", &n);
    SqrtDecomposition sd(n, 0);
    for (int i = 0; i < n; ++i) {
        int value; 
        scanf("%d", &value);
        sd.add(i, i, value);
    }
    int q; scanf("%d", &q);
    while (q--) {
        char t; scanf(" %c", &t);
        if (t == 'g') {
            int pos; scanf("%d", &pos);
            printf("%I64d ", sd.get(pos-1));
        } else {
            assert(t == 'a');
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            --l, --r;
            sd.add(l, r, x);
        }
    }
}