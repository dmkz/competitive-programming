#include <bits/stdc++.h>

bool check(int64_t a, int64_t b, int64_t c) {
    int64_t as = a*a;
    int64_t bs = b*b;
    int64_t cs = c*c;
    return as != 0 && bs != 0 && cs != 0 && (as+bs == cs || as+cs==bs || cs+bs==as);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int64_t n, k; std::cin >> n;
    std::vector<int64_t> diffs(n, 0);
    std::vector<int64_t> perm(n, 0);
    for (size_t it = 2; it <= n; ++it) {
        std::cout << "? " << 1 << ' ' << it << std::endl;
        std::cin >> diffs[it-1];
    }
    int64_t fpos = *std::max_element(diffs.begin(), diffs.end());
    int64_t first = std::max_element(diffs.begin(), diffs.end()) - diffs.begin() + 1;
    perm[0] = first;
    for (int64_t it = 1; it <= n; ++it) {
        std::cout << "? " << first << ' ' << it << std::endl;
        std::cin >> k;
        perm[k] = it;
    }

    std::cout << '!';
    for (auto& it : perm) {
        std::cout << ' ' << it;
    }
    return 0;
}
