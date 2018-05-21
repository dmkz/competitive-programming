#pragma GCC diagnostic ignored "-Wunused-result"
#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

int main() {
    int n, limit, pow;
    std::cin >> n >> limit >> pow;
    ll mod = 1;
    for (int p = 0; p < pow; ++p) {
        mod *= 10;
    }
    std::string s;
    std::cin >> s;
    s = '?' + s;
    std::vector<ll> answer(1+n, 0);
    answer[0] = 1;
    answer[1] = (s[1] - '0' <= limit);
    for (int curr = 2; curr <= n; ++curr) {
        ll number = 0, pow = 1;
        for (int prev = curr; curr - prev < 9 && prev >= 1; --prev, pow *= 10) {
            number += pow * (s[prev] - '0');
            if (number > limit) break;
            if (s[prev] == '0' && prev < curr) continue;
            answer[curr] = (answer[curr]+answer[prev-1]) % mod;
        }
    }
    std::cout << answer[n] << std::endl;
    return 0;
}