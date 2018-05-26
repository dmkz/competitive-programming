#include <stdio.h>
#include <vector>
#include <cassert>

typedef long long ll;

struct SqrtDecomposition {
    std::vector<int> arr;
    std::vector<ll> sum;
    
    const int GSIZE = 128;
    
    SqrtDecomposition(const std::vector<int>& vec) : arr(vec) {
        sum.assign(((int)arr.size() + GSIZE - 1) / GSIZE, 0);
        for (int g = 0; g < (int)sum.size(); ++g) {
            const int after = std::min((g+1)*GSIZE, (int)arr.size());
            auto& it = sum[g];
            for (int i = g * GSIZE; i < after; ++i) {
                it += arr[i];
            }
        }
    }
    
    void set(int pos, int value) {
        const int g = pos / GSIZE;
        sum[g] += (value - arr[pos]);
        arr[pos] = value;
    }
    
    ll get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        if (gl == gr) {
            ll s = 0;
            for (int i = l; i <= r; ++i) {
                s += arr[i];
            }
            return s;
        } else {
            ll s = 0;
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                s += arr[i];
            }
            for (int g = gl+1; g < gr; ++g) {
                s += sum[g];
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                s += arr[i];
            }
            return s;
        }
    }
    
};

int main() {
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) {
        scanf("%d", &it);
    }
    SqrtDecomposition sd(arr);
    int q; scanf("%d", &q);
    while (q--) {
        char t; int l, r;
        scanf(" %c %d %d", &t, &l, &r);
        if (t == 's') {
            printf("%I64d ", sd.get(l-1, r-1));
        } else {
            assert(t == 'u');
            sd.set(l-1, r);
        }
    }
    return 0;
}