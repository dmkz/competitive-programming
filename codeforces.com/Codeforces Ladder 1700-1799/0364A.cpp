/*
    Problem: 364A. Matrix
    
    Solution: math, number theory, divisors, combinatorics, O(n^2+sqrt(a))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
vi divisors(const int x) {
    vi answ{1}, stack{x};
    for (int i = 2; i * i <= x; ++i) {
        int j = x / i;
        if (i * j == x) {
            answ.push_back(i);
            stack.push_back(j);
        }
    }
    while (isz(stack) > 0 && stack.back() == answ.back()) {
        stack.pop_back();
    }
    while (isz(stack) > 0) {
        answ.push_back(stack.back());
        stack.pop_back();
    }
    return answ;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int a; std::string s;
    while (std::cin >> a >> s) {
        vi sumCnt(9*isz(s)+1,0);
        for (int i = 0; i < isz(s); ++i) {
            int sum = 0;
            for (int j = i; j < isz(s); ++j) {
                sum += s[j] - '0';
                assert(sum < isz(sumCnt));
                sumCnt[sum]++;
            }
        }
        int64_t answ = 0;
        if (a == 0) {
            int sumNonZero = 0;
            for (int i = 1; i < isz(sumCnt); ++i) {
                sumNonZero += sumCnt[i];
            }
            int sumAll = sumNonZero + sumCnt[0];
            answ = sumAll * 1LL * sumAll - sumNonZero * 1LL * sumNonZero;
        } else {
            for (auto d : divisors(a)) {
                const auto k = a / d;
                if (d < isz(sumCnt) && k < isz(sumCnt)) {
                    answ += sumCnt[d] * 1LL * sumCnt[k];
                }
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}