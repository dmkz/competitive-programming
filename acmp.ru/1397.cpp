#include <iostream>
#include <cstdint>

typedef int64_t Int;

bool is_possible(const Int extra, const Int n, const Int a, const Int b, const Int A, const Int B) {
    Int na = A / (a + 2 * extra);
    Int nb = B / (b + 2 * extra);
    if (nb == 0 || na == 0) return false;
    if (na >= n || nb >= n) return true;   
    return na * nb >= n || na >= (n + nb - 1) / nb || nb >= (n + na - 1) / na;
}

int main() {
    Int n, a, b, A, B;
    std::cin >> n >> a >> b >> A >> B;
    Int low = 0, high = 1e18L;
    while (high - low > 1) {
        Int mid = (low + high) >> 1;
        if (is_possible(mid, n, a, b, A, B) || is_possible(mid, n, b, a, A, B)) {
            low = mid;
        } else {
            high = mid;
        }
    }
    std::cout << low << std::endl;
    return 0;
}