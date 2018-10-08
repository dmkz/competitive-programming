/*
    Problem: 237C. Primes on Interval
    
    Solution: sieve, number theory, binary search, prefix sums, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    const int NMAX = (int)1e6;
    std::vector<int> is_prime(1+NMAX, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= NMAX; ++i) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= NMAX; j += i) {
            is_prime[j] = false;
        }
    }
    std::vector<int> sum(1+NMAX);
    for (int i = 1; i <= NMAX; ++i) {
        sum[i] = sum[i-1] + is_prime[i];
    }
    std::function<int(int,int)> get_sum = [&](int pos, int len) {
        return sum[pos+len-1] - sum[pos-1];
    };
    int a, b, k; scanf("%d %d %d", &a, &b, &k);
    int low = 0, high = b - a + 2;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        bool flag = true;
        for (int pos = a; pos + mid - 1 <= b; ++pos) {
            if (get_sum(pos, mid) < k) {
                flag = false; break;
            }
        }
        if (flag) high = mid; else low = mid;
    }
    if (high > b - a + 1) high = -1;
    printf("%d", high);
    return 0;
}