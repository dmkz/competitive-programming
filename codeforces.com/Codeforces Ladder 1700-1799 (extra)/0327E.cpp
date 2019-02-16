/*
    Problem: 327E. Axis Walking
    
    Solution: combinatorics, bitmasks, meet-in-the-middle, brute force, O(3^(N/2)*N^2+2^N)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <map>

typedef long long ll;

const int mod = (int)1e9+7;

int add(int a, int b) { return (a += b) >= mod ? (a -= mod) : a; }
int mul(int a, int b) { return int(1LL * a * b % mod); }
int sub(int a, int b) { return add(a, mod - b); }

int fact[25];

int solve1(const std::vector<int>& arr, int point) {
    // Solution of problem for 1 point
    const int n = (int)arr.size();
    int answ = 0, mask = 0, cnt = 0; ll sum = 0;
    while (true) {
        if (sum == point) {
            answ = add(answ, mul(fact[cnt], fact[n-cnt]));
        }
        int next = mask + 1;
        if (next == (1 << n)) { break; }
        #define xbit(value, x) ((value >> x) & 1)
        for (int bit = 0; bit < n && xbit(next, bit) != xbit(mask, bit); ++bit) {
            cnt += (xbit(mask, bit) == 0) ? +1 : -1;
            sum += (xbit(mask, bit) == 0) ? +arr[bit] : -arr[bit];
        }
        #undef xbit
        mask = next;
    }
    return answ;
}

int pow(int a, int n) {
    if (a < 2) return a;
    int ret = 1;
    while (n > 0) {
        if (n & 1) { ret *= a; }
        n >>= 1; a *= a;
    }
    return ret;
}

int solve2(const std::vector<int>& arr, int point1, int point2) {
    // solution of problem for 2 points:
    const int n = (int)arr.size();
    
    typedef std::pair<int,int> pii;
    typedef std::pair<ll,ll> pll;
    std::map<pll, std::map<pii, int>> fi, se;
    // precalc records for first and second halfs:
    const int fiLen = n / 2;
    const int seLen = n - fiLen;
    for (int mask = 0; mask < pow(3, fiLen); ++mask) {
        ll sum1 = 0, sum2 = 0;
        int cnt1 = 0, cnt2 = 0;
        for (int bit = 0, tmp = mask; bit < fiLen; ++bit, tmp /= 3) {
            sum1 += (tmp % 3 == 1) ? arr[bit] : 0;
            sum2 += (tmp % 3 == 2) ? arr[bit] : 0;
            cnt1 += (tmp % 3 == 1);
            cnt2 += (tmp % 3 == 2);
        }
        fi[pll(sum1,sum2)][pii(cnt1,cnt2)]++;
    }
    for (int mask = 0; mask < pow(3, seLen); ++mask) {
        ll sum1 = 0, sum2 = 0;
        int cnt1 = 0, cnt2 = 0;
        for (int bit = 0, tmp = mask; bit < seLen; ++bit, tmp /= 3) {
            sum1 += (tmp % 3 == 1) ? arr[fiLen + bit] : 0;
            sum2 += (tmp % 3 == 2) ? arr[fiLen + bit] : 0;
            cnt1 += (tmp % 3 == 1);
            cnt2 += (tmp % 3 == 2);
        }
        se[pll(sum1,sum2)][pii(cnt1,cnt2)]++;
    }
    int answ = 0;
    for (const auto& fiPairs : fi) {
        auto key = fiPairs.first;
        const ll need1 = point1 - key.first;
        const ll need2 = point2 - point1 - key.second;
        auto sePairs = se.find(pii(need1, need2));
        if (sePairs == se.end()) { continue; }
        // fi.sum1 + se.sum1 == point1
        // fi.sum2 + se.sum2 == point2 - point1
        // se.sum1 == point1 - fi.sum1
        // se.sum2 == point2 - point1 - fi.sum2
        for (auto& it : fiPairs.second) {
            for (auto& jt : sePairs->second) {
                int coeff = mul(it.second, jt.second);
                auto p1 = it.first;
                auto p2 = jt.first;
                int cnt1 = p1.first + p2.first;
                int cnt2 = p1.second + p2.second;
                answ = add(answ, mul(coeff, mul(mul(fact[cnt1], fact[cnt2]), fact[n - cnt1 - cnt2])));
            }
        }
    }
    return answ;
}

int main() {
    // precalc factorials
    fact[0] = 1;
    for (int i = 1; i <= 24; ++i) { fact[i] = mul(i, fact[i-1]); }
    // input:
    int n; 
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto &it : arr) { std::cin >> it; }
        std::sort(arr.begin(), arr.end());
        int k; std::cin >> k;
        std::vector<int> x(k);
        for (auto &it : x) { std::cin >> it; }
        std::sort(x.begin(), x.end());
        if (k == 0) { 
            std::cout << fact[n] << std::endl; 
            continue;
        }
        if (k == 1) {
            std::cout << sub(fact[n], solve1(arr, x[0])) << std::endl;
            continue;
        }
        int answ = fact[n];
        answ = sub(answ, solve1(arr, x[0]));
        answ = sub(answ, solve1(arr, x[1]));
        answ = add(answ, solve2(arr, x[0], x[1]));
        std::cout << answ << std::endl;
    }
    return 0;
}