/*
    Problem: 1202C. You Are Given a WASD-string...
    Solution: brute force, math, strings, bracket sequences, O(n)
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
typedef long long ll;
typedef std::vector<int> vi;
vi getPrefixSums(vi arr) {
    vi answ{0};
    for (auto it : arr) answ.push_back(answ.back() + it);
    return answ;
}
vi getMaxOnPref(vi arr) {
    if (!isz(arr)) return vi{};
    vi max{arr[0]};
    for (int i = 1; i < isz(arr); i++) {
        max.push_back(std::max(max.back(), arr[i]));
    }
    return max;
}
vi getMinOnPref(vi arr) {
    if (!isz(arr)) return vi{};
    vi res{arr[0]};
    for (int i = 1; i < isz(arr); i++) { 
        res.push_back(std::min(res.back(), arr[i]));
    }
    return res;
}
vi getMaxOnSuff(vi arr) {
    if (!isz(arr)) return vi{};
    std::reverse(all(arr));
    auto ret = getMaxOnPref(arr);
    std::reverse(all(ret));
    return ret;
}
vi getMinOnSuff(vi arr) {
    if (!isz(arr)) return vi{};
    std::reverse(all(arr));
    auto ret = getMinOnPref(arr);
    std::reverse(all(ret));
    return ret;
}
int getMinDiam(vi arr, int item) {
    arr = getPrefixSums(arr);
    vi minPref = getMinOnPref(arr), maxPref = getMaxOnPref(arr);
    vi minSuff = getMinOnSuff(arr), maxSuff = getMaxOnSuff(arr);
    int diam = std::max(item, maxPref.back()) - std::min(item, minPref.back()) + 1;
    for (int i = 0; i < isz(arr); i++) {
        // after ith symbol
        int min = std::min(minPref[i], minSuff[i] + item);
        int max = std::max(maxPref[i], maxSuff[i] + item);
        diam = std::min(diam, max - min + 1);
    }
    return diam;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int t; std::cin >> t;
    while (t--) {
        std::string s; std::cin >> s;
        vi vertical, horizontal;
        for (auto it : s) {
            if (it == 'S') { vertical.push_back(-1); }
            if (it == 'W') { vertical.push_back(+1); }
            if (it == 'A') { horizontal.push_back(-1); }
            if (it == 'D') { horizontal.push_back(+1); }
        }
        ll answ = LLONG_MAX;
        for (int itv = -1; itv <= 1; ++itv) {
            for (int ith = -1; ith <= 1; ++ith) {
                if (itv * itv + ith * ith <= 1) {
                    answ = std::min(answ, getMinDiam(vertical, itv) * 1LL * getMinDiam(horizontal, ith));
                }
            }
        }
        std::cout << answ << "\n";
    }
    return 0;
}