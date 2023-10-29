#include "template.hpp"
const int X = (int)1e6+1;
int main() {
    int n, m; std::cin >> n >> m;
    vi a(n); std::cin >> a;
    vvi pos(X);
    for (int i = 0; i < n; i++)
        pos[a[i]] << i;
    int left = n, right = -1;
    int best = n+1;
    for (int item = 1; item < X; item++) {
        auto &pp = pos[item];
        if (!isz(pp))
            continue;
        if (m > isz(pp)) {
            m -= isz(pp);
            remin(left, pp.front());
            remax(right, pp.back());
        } else {
            for (int i = 0; i + m - 1 < isz(pp); i++) {
                // pp[i]
                // pp[i+m-1]
                int nl = std::min(left, pp[i]);
                int nr = std::max(right, pp[i+m-1]);
                remin(best, nr-nl+1);
            }
            break;
        }
    }
    assert(best != n+1);
    std::cout << best << std::endl;
}
