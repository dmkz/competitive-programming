#include <bits/stdc++.h>
using ll = long long;
const ll INF = (ll)1e18L;
int main() {
    int n, k; std::cin >> n >> k;
    std::vector<ll> a(n);
    for (auto &it : a)
        std::cin >> it;

    ll upperBound = (ll)1e13;
    std::vector dpFromBottom(2, std::vector(k+1, -INF));
    auto dpFromTop = dpFromBottom;
    
    dpFromBottom[0][1] = -a[0];
    dpFromTop[0][1] = -(upperBound - a[0]);

    ll answer{};
    for (int i = 1; i < n; i++) {
        ll fromBottom = a[i];
        ll fromTop = upperBound - a[i];
        for (int j = k; j >= 2; j--) {
            ll bestAnswerAtK = std::max<ll>(
                dpFromBottom[i%2^1][j - 1] + fromBottom,
                dpFromTop[i%2^1][j - 1] + fromTop
            );
            if (j == k) {
                // relax the global answer
                answer = std::max<ll>(answer, bestAnswerAtK);
            }
            if (bestAnswerAtK > 0) {
                dpFromBottom[i%2][j] = std::max<ll>(dpFromBottom[i%2^1][j],
                    bestAnswerAtK - fromBottom);
                dpFromTop[i%2][j] = std::max<ll>(dpFromTop[i%2^1][j],
                    bestAnswerAtK - fromTop);
            }
        }

        dpFromBottom[i%2][1] = std::max<ll>(-a[i], dpFromBottom[i%2^1][1]);
        dpFromTop[i%2][1] = std::max<ll>(-(upperBound - a[i]), dpFromTop[i%2^1][1]);
    }
    std::cout << answer << '\n';
}
