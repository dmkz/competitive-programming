/*
    Problem: 547B. Mike and Feet
    
    Solution: binary search, sparse table, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

namespace ST {
    const int NMAX = 200 * 1000, PMAX = 18;
    int log2[1+NMAX], min[PMAX][NMAX];
    void init() {
        for (int i = 2; i <= NMAX; ++i) { log2[i] = 1 + log2[i/2]; }
    }
    template<typename T>
    void build(const std::vector<T>& arr) {
        for (int i = 0; i < isz(arr); ++i) { min[0][i] = arr[i]; }
        for (int p = 1; p < PMAX; ++p) {
            for (int i = 0; i + (1 << p) - 1 < isz(arr); ++i) {
                min[p][i] = std::min(min[p-1][i], min[p-1][i+(1<<(p-1))]);
            }
        }
    }
    int getMin(int i, int j) {
        assert(i <= j);
        const int len = j - i + 1;
        const int pow = log2[len];
        return std::min(min[pow][i], min[pow][j+1-(1 << pow)]);
    }
}

typedef std::pair<int,int> pii;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

int main() {
    using namespace ST;
    init();
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        vi arr(n); vii pairs(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
            pairs[i] = pii(arr[i],i);
        }
        std::sort(all(pairs));
        build(arr);
        vi answ(1+isz(arr), INT_MIN);
        for (auto p : pairs) {
            const int min = p.first;
            const int pos = p.second;
            int begin = pos, end = pos;
            {
                int low = pos, high = isz(arr);
                while (high - low > 1) {
                    int mid = (low + high) / 2;
                    if (getMin(pos,mid) == min) { low = mid; }
                    else { high = mid; }
                }
                end = low;
            }
            {
                int low = -1, high = pos;
                while (high - low > 1) {
                    int mid = (low + high) / 2;
                    if (getMin(mid,pos) == min) { high = mid; }
                    else { low = mid; }
                }
                begin = high;
            }
            int len = end - begin + 1;
            answ[len] = std::max(answ[len], min);
        }
        for (int len = n-1; len >= 1; --len) {
            answ[len] = std::max(answ[len], answ[len+1]);
        }
        for (int i = 1; i <= n; ++i) { std::cout << answ[i] << ' '; }
        std::cout << std::endl;
    }
    return 0;
}