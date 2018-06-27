/*
    "Дроби": математика, наибольший общий делитель, бинарный поиск
*/

#include <iostream>

typedef long long ll;

inline ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    ll p, q;
    std::cin >> p >> q;
    
    while (p != 0) {
        auto gcd = ::gcd(p, q);
        p /= gcd;
        q /= gcd;
        ll low = 1, high = q;
        while (high - low > 1) {
            ll mid = (low + high) / 2;
            if (p * mid >= q) {
                high = mid;
            } else {
                low = mid;
            }
        }
        std::cout << high << " ";
        p = p * high - q;
        q *= high;
    }
    
    return 0;
}