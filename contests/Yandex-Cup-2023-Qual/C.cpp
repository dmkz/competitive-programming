#include "template.hpp"
#include "debug.hpp"
#include "numeric.hpp"
using namespace algos::numeric;
const int mod = (int)1e9+7;
using Int = IntMod<mod>;
// 0000  0
// 0001  1
// 0010  2
// 0011  3
// 0100  4
// 0101  5
// 0110  6
// 0111  7
// 1000  8
// 1001  9
// 1010 10
// 1011 11
// 1100 12
// 1101 13
// 1110 14
// 1111 15
ll cntOnes(ll n, int bit) {
    ll gsize = (ll(1) << (bit+1));
    ll mid = gsize / 2;
    ll res = n / gsize * mid;
    n %= gsize;
    if (n >= mid)
        res += n - mid + 1;
    return res;
}
int main() {
    int tt; std::cin >> tt;
    while (tt --> 0) {
        ll n; std::cin >> n;
        Int pow2 = 1, answ = 0;
        for (int bit = 0; bit <= 59; bit++) {
            Int cnt = cntOnes(n, bit);
            watch(bit, cnt);
            answ += cnt * cnt * pow2;
            pow2 *= 2;
        }
        std::cout << answ << std::endl;
    }
}
