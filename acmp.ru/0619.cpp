#include <iostream>
#include <iomanip>
#include <vector>

typedef long double Real;

int main() {
    int n, sum; std::cin >> n >> sum;
    if (sum < n || sum > 6 * n) {
        std::cout << "0";
        return 0;
    }
    std::vector<Real> curr(1+sum), next(1+sum);
    curr[0] = 1;
    int limit = 0;
    for (int i = 1; i <= n; ++i) {
        limit = std::min(limit+6, sum);
        for (int s = 0; s <= limit; ++s) {
            Real value = 0;
            for (int score = 1; score <= 6; ++score) {
                if (s - score >= 0) {
                    value += curr[s-score];
                }
            }
            next[s] = value / 6;
        }
        curr.swap(next);
        for (int s = 0; s <= limit; ++s) {
            next[s] = 0;
        }
    }
    std::cout << std::fixed << std::setprecision(6) << curr[sum];
    return 0;
}