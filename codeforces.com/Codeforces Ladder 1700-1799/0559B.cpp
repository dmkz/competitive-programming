/*
    Problem: 559B. Equivalent Strings
    
    Solution: strings, divide and conquer, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
void sort(std::string& a, int begin, int after) {
    const int len = (after - begin);
    if (len % 2 == 0) {
        const int mid = begin + len / 2;
        sort(a, begin, mid);
        sort(a, mid, after);
        int i = begin, j = mid;
        while (i < mid && a[i] == a[j]) { i++,j++; }
        if (i < mid && a[i] > a[j]) {
            while (i < mid) { std::swap(a[i++],a[j++]); }
        }
    }
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (std::string s, t; std::cin >> s >> t; std::cout << std::endl) {
        sort(s, 0, (int)s.size());
        sort(t, 0, (int)t.size());
        std::cout << (s == t ? "YES\n" : "NO\n");
    }
    return 0;
}