#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

int gcd(int a, int b) {
    while (b != 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

struct DataStruct {
    std::vector<int> arr, gcd;
    
    const int GSIZE = 128;
    
    DataStruct(int size = 0, int item = 0) {
        arr.assign(size, item);
        gcd.assign(size / GSIZE+1, item);
    }
    
    void set(int p, int v) {
        arr[p] = v;
        const int g = p / GSIZE;
        gcd[g] = v;
        const int begin = g * GSIZE;
        const int after = std::min(begin + GSIZE, (int)arr.size());
        for (int i = begin; i < after; ++i) {
            gcd[g] = ::gcd(arr[i], gcd[g]);
        }
    }
    
    int get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        int answ = arr[l];
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                answ = ::gcd(answ, arr[i]);
            }
        } else {
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                answ = ::gcd(answ, arr[i]);
            }
            for (int g = gl+1; g < gr; ++g) {
                answ = ::gcd(answ, gcd[g]);
            }
            for (int i = gr * GSIZE; i <= r; ++i) {
                answ = ::gcd(answ, arr[i]);
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