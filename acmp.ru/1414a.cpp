#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
  
typedef long long ll;
  
struct Group {
    ll sum, sum2, count;
      
    void add(ll value) {
        sum += value;
        sum2 += value * value;
        count++;
    }
};
  
struct SqrtDecomposition {
    std::vector<ll> arr;
    std::vector<Group> group;
      
    const int GSIZE = 512;
      
    SqrtDecomposition(const int size) {
        arr.assign(size, 0);
        group.assign((size + GSIZE-1)/GSIZE, Group{0,0,0});
    }
      
    void push(int g) {
        const int begin = g*GSIZE;
        const int after = std::min((g+1)*GSIZE, (int)arr.size());
        const auto& gr = group[g];
        arr[begin] += gr.sum2;
        ll curr = gr.sum2;
        for (int i = begin+1; i < after; ++i) {
            const int p = i - begin - 1;
            curr += gr.count * (1 + 2 * p) + 2 * gr.sum;
            arr[i] += curr;
        }
    }
      
    void push_all() {
        for (int g = 0; g < (int)group.size(); ++g) {
            push(g);
        }
    }
      
    void inc(int left, int right) {
        const int gl = left  / GSIZE;
        const int gr = right / GSIZE;
        if (gl == gr) {
            for (int i = left; i <= right; ++i) {
                arr[i] += ll(i-left+1)*(i-left+1);
            }
        } else {
            for (int i = left, limit = (gl+1) * GSIZE; i < limit; ++i) {
                arr[i] += ll(i-left+1)*(i-left+1);
            }
            for (int g = gl+1; g < gr; ++g) {
                group[g].add(g*GSIZE-left+1);
            }
            for (int i = gr*GSIZE; i <= right; ++i) {
                arr[i] += ll(i-left+1)*(i-left+1);
            }
        }
    }
};
  
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, q;
    std::cin >> n >> q;
    //scanf("%d %d", &n, &q);
      
    SqrtDecomposition sdl(n), sdr(n);
      
    while (q--) {
        int begin, end;
        std::cin >> begin >> end;
        //scanf("%d %d", &begin, &end);
        --begin, --end;
        if (begin <= end) {
            sdl.inc(begin, end);
        } else {
            sdr.inc(n-1-begin, n-1-end);
        }
    }
    sdl.push_all();
    sdr.push_all();
    std::reverse(sdr.arr.begin(), sdr.arr.end());
    for (int i = 0; i < n; ++i) {
        //printf("%I64d\n", sdl.arr[i]+sdr.arr[i]);
        std::cout << sdl.arr[i]+sdr.arr[i] << '\n';
    }
    return 0;
}