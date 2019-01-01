/*
    Problem: 258C. Little Elephant and LCM
    
    Solution: combinatorics, math, number theory, prefix sums, lcm, O(n*cbrt(n)*log(MOD))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cassert>

typedef std::vector<int> vi;

const int AMAX = (int)1e5;
const int MOD = (int)1e9+7;

int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}

int sub(int u, int v) {
    return (u -= v) < 0 ? u + MOD : u;
}

int mul(int u, int v) {
    return int(1LL * u * v % MOD);
}

int pow(int a, int n) {
    int ret = 1;
    while (n > 0) {
        if (n & 1) {
            ret = mul(ret, a);
        }
        n /= 2;
        a = mul(a,a);
    }
    return ret;
}

vi divisors(int n) {
    vi answ{1}, stack{n};
    for (int i = 2; i * i <= n; ++i) {
        int j = n / i;
        if (i * j == n) {
            answ.push_back(i);
            stack.push_back(j);
        }
    }
    if (stack.back() == answ.back()) { stack.pop_back(); }
    while (!stack.empty()) { answ.push_back(stack.back()); stack.pop_back(); }
    return answ;
}

int solve(const vi& arr) {
    // Calculate suffix sums over number of items in array:
    int max = *std::max_element(arr.begin(), arr.end());
    vi countNotLess(1+AMAX);
    for (int it : arr) { countNotLess[it]++; }
    for (int i = AMAX-1; i >= 0; --i) {
        countNotLess[i] += countNotLess[i+1];
    }
    assert(countNotLess[1] == (int)arr.size());
    // Calculate answer:
    vi temp; int answ = 0;
    for (int curr = 1; curr <= max; ++curr) {
        // Get divisors:
        vi divs = divisors(curr);
        temp.assign(divs.size(), 0);
        // Calculate number of possible places for each divisors:
        for (int i = 0; i < (int)divs.size(); ++i) {
            int it = divs[i];
            temp[i] = countNotLess[it];
        }
        for (int i = 0; i+1 < (int)divs.size(); ++i) {
            temp[i] -= temp[i+1];
        }
        // Calculate varians for choosing places for divisors less then `curr`:
        int res = 1;
        for (int i = 1; i < (int)temp.size(); ++i) {
            res = mul(res, pow(i, temp[i-1]));
        }
        // at least one item must be equal to `curr`:
        // nVar^nPlaces-(nVar-1)^nPlaces
        int nVariants = (int)temp.size();
        int nPlaces = temp.back();
        res = mul(res, sub(
            pow(nVariants,nPlaces),
            pow(nVariants-1,nPlaces)
        ));
        answ = add(answ, res);
    }
    return answ;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vi arr(n); for (auto &it : arr) { std::cin >> it; }
        std::cout << solve(arr) << std::endl;
    }
    return 0;
}