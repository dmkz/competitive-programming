#include "template.hpp"
#include "numeric.hpp"
const int mod = 3;
using namespace algos::numeric;
using Int = IntMod<mod>;

int main() {
    auto count = [&](ll R, int k) {
        ll x = (ll)powl(R, 1.0L / k);
        while (pow(ld(x),k) > R) x--;
        while (pow(ld(x)+1,k) <= R) x++;
        return x;
    };
    ll x;
while (std::cin >> x) {
    auto f = [&](ll R) {
        // кол-во <= R
        return count(R, 2) + count(R, 3) - count(R, 6);
    };
    ll low = 0, high = (ll)1e16L;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (f(mid) >= x) high = mid;
        else low = mid;
    }
    std::cout << high << std::endl;
}
}
