/*
    Problem: 111B. Petya and Divisors
    
    Solution: number theory, math, divisors, O(n * sqrt(XMAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::pair<int,int> pii;
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
vi solve(const std::vector<pii>& arr) {
    int xmax = 0;
    for (auto &it : arr) { xmax = std::max(xmax, it.first); }
    vi maxPos(1+xmax,-1), answ;
    for (int i = 0; i < isz(arr); ++i) {
        const int begin = i - arr[i].second;
        const auto divs = divisors(arr[i].first);
        int cnt = 0;
        for (auto it : divs) {
            cnt += (maxPos[it] < begin);
            maxPos[it] = i;
        }
        answ.push_back(cnt);
    }
    return answ;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        std::vector<pii> arr(n);
        for (auto &it : arr) { 
            std::cin >> it.first >> it.second;
        }
        vi answ = solve(arr);
        for (auto it : answ) {
            std::cout << it << '\n';
        }
    }
    return 0;
}